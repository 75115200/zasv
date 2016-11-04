package com.tencent.radio.ugc.record.widget;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.support.annotation.ColorInt;
import android.support.annotation.NonNull;
import android.util.AttributeSet;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.widget.OverScroller;

import java.util.Formatter;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Locale;

/**
 * <pre>
 * Author: taylorcyang@tencent.com
 * Date:   2016-10-17
 * Time:   21:26
 * Life with Passion, Code with Creativity.
 * </pre>
 */
public class AudioTimeRulerView extends View implements GestureDetector.OnGestureListener {
    private static final String TAG = "AudioTimeRulerView";

    private final Paint mPathPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint mTextPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Path mRulerPath = new Path();
    private final Path mPointerPath = new Path();

    /** how tall the ruler is **/
    private float mRulerHeight;
    /** how tall the smaller line is */
    private float mRulerSecondaryHeight;
    /** how long one second is, in the ruler. */
    private float mRulerSecondWidth;
    /** how many ruler-line in one second */
    private int mRulerPrecision;
    /** how may distance a text should keep away from the ruler line */
    private float mRulerTextPadding;

    /** how many audio scale in on second */
    private int mWaveScalePrecision;
    private float mWaveStrokeWidth;

    private float mRulerStrokeWidth;
    private float mPointerStrokeWidth;
    private float mPointerTriangleWidth;

    @ColorInt
    private int mRulerColor = Color.WHITE;
    @ColorInt
    private int mPointerColor = Color.WHITE;
    @ColorInt
    private int mWaveColor = Color.WHITE;

    //state
    private float mPointerPositionX;

    //text display
    private StringBuilder mCachedTimeTextStingBuilder = new StringBuilder();
    private Formatter mCachedTimeTextFormatter = new Formatter(mCachedTimeTextStingBuilder, Locale.US);

    // Motion
    private final GestureDetector mGestureDetector;
    private final OverScroller mScroller;

    private float mWaveScrollX;
    private int mMinScrollX;

    // MARK: data
    private RulerAdapter mRulerAdapter;

    // MARK: path
    private LinkedList<PathSegment> mLivePathSegments = new LinkedList<>();
    private LinkedList<PathSegment> mCrappedPathSegments = new LinkedList<>();

    public AudioTimeRulerView(Context context) {
        this(context, null);
    }

    public AudioTimeRulerView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public AudioTimeRulerView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);

        mGestureDetector = new GestureDetector(context, this);
        mScroller = new OverScroller(context);

        initFakeData();
    }

    public RulerAdapter getRulerAdapter() {
        return mRulerAdapter;
    }

    public void setRulerAdapter(RulerAdapter rulerAdapter) {
        mRulerAdapter = rulerAdapter;

        notifyDataSetChanged();
    }

    private void initFakeData() {
        mRulerHeight = 50;
        mRulerSecondaryHeight = 15;
        mRulerSecondWidth = 200;
        mRulerPrecision = 4;
        mWaveScalePrecision = 20;
        mWaveStrokeWidth = 2;

        mPointerColor = Color.CYAN;
        mRulerColor = Color.WHITE;
        mRulerTextPadding = 10;
        mRulerStrokeWidth = 2;
        mPointerStrokeWidth = 2;
        mPointerTriangleWidth = 30;

        mPointerPositionX = 230;

        mTextPaint.setColor(Color.WHITE);
        mTextPaint.setTextSize(30);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        drawRuler(canvas);

        drawWave(canvas);

        drawPointer(canvas);
    }

    private void drawRuler(Canvas canvas) {
        // draw time
        int startTime = getCurrentStartTime();
        float offset = getCurrentScrollOffset();

        mPathPaint.setStyle(Paint.Style.STROKE);
        mPathPaint.setColor(mRulerColor);
        mPathPaint.setStrokeWidth(mRulerStrokeWidth);

        // draw ruler line
        canvas.save();
        canvas.translate(-offset, 0);
        canvas.drawPath(mRulerPath, mPathPaint);
        canvas.restore();

        // draw ruler time test
        float textX = -offset + mRulerTextPadding;
        final float textY = mRulerHeight - mRulerSecondaryHeight - mRulerTextPadding;

        while (textX < getWidth()) {
            if (startTime >= 0) {
                CharSequence timeText = getTimeText(startTime);
                canvas.drawText(timeText, 0, timeText.length(), textX, textY, mTextPaint);
            }

            textX += mRulerSecondWidth;
            startTime++;
        }
    }

    private void drawPointer(Canvas canvas) {
        mPathPaint.setStyle(Paint.Style.FILL_AND_STROKE);
        mPathPaint.setStrokeWidth(mPointerStrokeWidth);
        mPathPaint.setColor(mPointerColor);

        canvas.save();
        canvas.translate(mPointerPositionX, mRulerHeight);
        canvas.drawPath(mPointerPath, mPathPaint);
        canvas.restore();
    }

    @NonNull
    private CharSequence getTimeText(int second) {
        int minute = second / 60;
        second %= 60;

        mCachedTimeTextStingBuilder.delete(0, mCachedTimeTextStingBuilder.length());
        mCachedTimeTextFormatter.format("%02d:%02d", minute, second);

        return mCachedTimeTextStingBuilder;
    }

    /**
     * @return second
     */
    private int getCurrentStartTime() {
        int time = (int) (mWaveScrollX / mRulerSecondWidth);
        if (mWaveScrollX < 0) {
            // normalize negative
            time--;
        }
        return time;
    }

    private float getCurrentScrollOffset() {
        int offset = (int) (mWaveScrollX % mRulerSecondWidth);
        if (offset >= 0) {
            return offset;
        } else {
            // normalize negative
            return mRulerSecondWidth + offset;
        }
    }

    private void drawWave(Canvas canvas) {
        updateWavePath();

        float x = -getCurrentScrollOffset();
        Iterator<PathSegment> it = mLivePathSegments.iterator();
        while (it.hasNext()) {
            PathSegment pathSegment = it.next();

            pathSegment.drawAt(canvas, x, mRulerHeight);
            x += mRulerSecondWidth;
        }
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        constructRulerPath(w, h, oldw, oldh);
        constructPointerPath(w, h, oldw, oldh);

        mPointerPositionX = w / 2;
        mMinScrollX = -w / 2;
    }

    private void constructRulerPath(int width, int height, int oldWidth, int oldHeight) {
        if (width == oldWidth) return;

        mRulerPath.rewind();
        mRulerPath.moveTo(0, mRulerHeight);
        mRulerPath.lineTo(getWidth() + mRulerSecondWidth, mRulerHeight);

        final int linesToDraw = (int) (mRulerPrecision * Math.ceil((width + mRulerSecondWidth) / mRulerSecondWidth));
        final float precision = mRulerSecondWidth / mRulerPrecision;

        mRulerPath.moveTo(0, mRulerHeight);
        for (int i = 0; i < linesToDraw; i++) {
            float rulerHeight;
            if ((i % mRulerPrecision) == 0) {
                //lone ruler
                rulerHeight = mRulerHeight;
            } else {
                //short ruler
                rulerHeight = mRulerSecondaryHeight;
            }

            mRulerPath.rLineTo(0, -rulerHeight);
            mRulerPath.rMoveTo(precision, rulerHeight);
        }
    }

    private void constructPointerPath(int width, int height, int oldWidth, int oldHeight) {
        if (height == oldHeight) return;

        height -= mRulerHeight;

        @SuppressWarnings("SuspiciousNameCombination")
        final float triangleHeight = mPointerTriangleWidth;

        mPointerPath.rewind();
        //draw triangle first
        mPointerPath.moveTo(0, triangleHeight);
        mPointerPath.rLineTo(-mPointerTriangleWidth / 2, -triangleHeight);
        mPointerPath.rLineTo(mPointerTriangleWidth, 0);
        mPointerPath.close();

        //draw vertical line
        mPointerPath.moveTo(0, triangleHeight);
        mPointerPath.rLineTo(0, height - triangleHeight);
    }

    private void updateWavePath() {
        if (mRulerAdapter == null) {
            recycleAllPathSegment();
            return;
        }

        final long startTimeMillis = getCurrentStartTime() * 1000;
        final long pathTimeDuration = 1000;
        final int pathSegmentCountToDisplay =
                (int) Math.ceil((getWidth() + getCurrentScrollOffset()) / mRulerSecondWidth);
        final long endTimeMillis =
                Math.min(startTimeMillis + pathTimeDuration * pathSegmentCountToDisplay,
                        mRulerAdapter.getTotalTime());
        final long lastSegmentStartTime = endTimeMillis - (1 + (endTimeMillis - 1) % pathTimeDuration);

        if (getLivePathSegmentsStartTime() == startTimeMillis &&
                getLivePathSegmentsEndTime() == endTimeMillis) {
            // the same
            return;
        }
        //// STOPSHIP: 04/11/2016
        //// TODO: 04/11/2016
        recycleAllPathSegment();
        addPathSegment(startTimeMillis, endTimeMillis, pathTimeDuration, true);
//
//        if (mLivePathSegments.isEmpty()) {
//            addPathSegment(startTimeMillis, endTimeMillis, pathTimeDuration, true);
//        } else {
//            PathSegment lastSegment = mLivePathSegments.getLast();
//            if (lastSegment.startTime + lastSegment.duration != endTimeMillis) {
//                // remove partial built segment
//                mLivePathSegments.removeLast();
//            }
//            addPathSegmentIncrementally(startTimeMillis, pathTimeDuration, endTimeMillis, lastSegmentStartTime);
//        }
    }

    private void addPathSegmentIncrementally(
            long startTimeMillis,
            long pathTimeDuration,
            long endTimeMillis,
            long lastSegmentStartTime) {

        // full rebuild
        if (mLivePathSegments.isEmpty()) {
            addPathSegment(startTimeMillis, endTimeMillis, pathTimeDuration, true);
            return;
        }

        // try to remove old item and add new ones
        final long firstPathSegmentTime = mLivePathSegments.getFirst().startTime;
        final long lastPathSegmentTime = mLivePathSegments.getLast().startTime;

        if (endTimeMillis < firstPathSegmentTime || startTimeMillis > lastPathSegmentTime) {
            // can't reuse any pathSegment
            // full rebuild
            recycleAllPathSegment();
            addPathSegment(startTimeMillis, endTimeMillis, pathTimeDuration, true);
            return;

        }

        if (startTimeMillis > firstPathSegmentTime) {
            // remove header old items
//            while (!mLivePathSegments.isEmpty()) {
            while (true) {
                PathSegment first = mLivePathSegments.getFirst();
                if (first.startTime < startTimeMillis) {
                    recyclePathSegment(mLivePathSegments.removeFirst());
                } else {
                    break;
                }
            }
        }

        if (lastSegmentStartTime < getLivePathSegmentsEndTime()){
            // remove tail old items
//            while (!mLivePathSegments.isEmpty()) {
            while (true) {
                PathSegment last = mLivePathSegments.getLast();
                if (last.startTime < lastSegmentStartTime) {
                    recyclePathSegment(mLivePathSegments.removeLast());
                } else {
                    break;
                }
            }
        }


    }

    private long getLivePathSegmentsStartTime() {
        if (!mLivePathSegments.isEmpty()) {
            return mLivePathSegments.getFirst().startTime;
        }
        return -1;
    }

    private long getLivePathSegmentsEndTime() {
        if (!mLivePathSegments.isEmpty()) {
            PathSegment last = mLivePathSegments.getLast();
            return last.startTime + last.duration;
        }
        return -1;
    }

    /**
     * @param startTime
     * @param timeDuration
     * @param frontOrBack  true to add at front, false to add at tail
     */
    private void addPathSegment(long startTime, long endTime, long timeDuration, boolean frontOrBack) {
        final ListIterator<PathSegment> listIterator;
        if (frontOrBack || mLivePathSegments.isEmpty()) {
            listIterator = mLivePathSegments.listIterator(0);
        } else {
            // the last item
            listIterator = mLivePathSegments.listIterator(mLivePathSegments.size());
        }

        while (startTime < endTime) {
            final PathSegment ps = obtainPathSegment();
            long duration = Math.min(endTime - startTime, timeDuration);
            ps.constructPath(startTime, duration);

            // inset item
            listIterator.add(ps);

            startTime += duration;
        }
    }

    private void recycleAllPathSegment() {
        Iterator<PathSegment> it = mLivePathSegments.iterator();
        while (it.hasNext()) {
            PathSegment ps = it.next();
            recyclePathSegment(ps);
            it.remove();
        }
    }

    private void recyclePathSegment(@NonNull PathSegment pathSegment) {
        pathSegment.recycle();
        mCrappedPathSegments.add(pathSegment);
    }

    @NonNull
    private PathSegment obtainPathSegment() {
        if (!mCrappedPathSegments.isEmpty()) {
            return mCrappedPathSegments.pop();
        }

        return new PathSegment();
    }

    public void notifyDataSetChanged() {
        recycleAllPathSegment();
        updateWavePath();
    }

    public void notifyDataAdded(long startTime, long duration) {

    }

    public interface RulerAdapter {
        long getTotalTime();

        /** @return ranged [0, 100] */
        int getDataForTime(long timeMillis);
    }

    /**
     * 1 second time wave path.
     */
    private class PathSegment {
        public final Path path = new Path();
        public long startTime;
        public long duration;
        public float totalHeight;

        public void constructPath(long startTime, long duration) {
            totalHeight = (int) ((getHeight() - mRulerHeight) / 2);

            if (this.startTime != startTime || this.duration > duration) {
                // construct new
                path.rewind();
                addWaveToPath(0, startTime, duration);

                this.startTime = startTime;
                this.duration = duration;
            } else {
                // incremental construct
                addWaveToPath(this.duration, startTime - this.duration, duration - this.duration);
                this.duration = duration;
            }
        }

        /**
         * @param originTime relative to 0, indicate where to draw the first line.
         * @param startTime  startTime to get data
         * @param duration   time length
         */
        private void addWaveToPath(long originTime, long startTime, long duration) {
            final float rulerXGap = mRulerSecondWidth / mWaveScalePrecision;
            final float rulerTimeGapMs = 1000 / mWaveScalePrecision;
            final float startX = originTime / rulerTimeGapMs * rulerXGap;
            final long end = startTime + duration;

            path.moveTo(startX, 0);
            while (startTime < end) {
                float height = mRulerAdapter.getDataForTime(startTime);
                // normalize
                height = height * totalHeight / 100;

                path.rMoveTo(0, -height);
                path.rLineTo(0, 2 * height);

                path.rMoveTo(rulerXGap, -height);

                startTime += rulerTimeGapMs;
            }
        }

        public void drawAt(Canvas canvas, float x, float y) {
            mPathPaint.setColor(mWaveColor);
            mPathPaint.setStrokeWidth(mWaveStrokeWidth);

            canvas.save();
            canvas.translate(x, totalHeight + y);
            canvas.drawPath(path, mPathPaint);
            canvas.restore();
        }

        public void recycle() {
            path.rewind();
            startTime = duration = 0;
            totalHeight = 0;
        }

        @Override
        public String toString() {
            return "PathSegment{" +
                    "startTime=" + startTime +
                    ", duration=" + duration +
                    ", totalHeight=" + totalHeight +
                    '}';
        }
    }

    // Mark: Gesture and scroll
    @Override
    public void scrollTo(int x, int y) {
        mScroller.startScroll((int) mWaveScrollX, 0, x, 0);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return mGestureDetector.onTouchEvent(event);
    }

    @Override
    public void computeScroll() {
        super.computeScroll();

        if (mScroller.computeScrollOffset()) {
            mWaveScrollX = mScroller.getCurrX();
            invalidate();
        }
    }

    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
        // stop previous anime
        mScroller.abortAnimation();

        mWaveScrollX += distanceX;

        invalidate();
        return true;
    }

    @Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        // stop previous anime
        mScroller.abortAnimation();

        mScroller.fling(
                (int) mWaveScrollX, 0,
                (int) -velocityX, 0,
                //min/max X
                mMinScrollX,
                100000,
                0, 0,
                getWidth() / 2, 0);

        invalidate();
        return true;
    }

    @Override
    public boolean onDown(MotionEvent e) {
        mScroller.abortAnimation();
        return true;
    }

    @Override
    public void onShowPress(MotionEvent e) {

    }

    @Override
    public boolean onSingleTapUp(MotionEvent e) {
        return true;
    }

    @Override
    public void onLongPress(MotionEvent e) {

    }

}
