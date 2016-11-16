package com.tencent.radio.ugc.record.widget;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.drawable.Drawable;
import android.support.annotation.ColorInt;
import android.support.annotation.IntDef;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.widget.OverScroller;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.ListIterator;

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

    /** user can scroll the view */
    public static final int MODE_SCROLL_BY_TOUCH = 0;
    /**
     * user cannot scroll the view,
     * called {@link #scrollToTime(long, boolean)} to scroll the view
     */
    public static final int MODE_SCROLL_BY_TIME = 1;
    /**
     * user cannot scroll the view, when new data added,
     * the view will scroll to new position automatically
     */
    public static final int MODE_FOLLOW_NEW_DATA = 2;

    @IntDef({
            MODE_SCROLL_BY_TOUCH,
            MODE_SCROLL_BY_TIME,
            MODE_FOLLOW_NEW_DATA
    })
    @Retention(RetentionPolicy.SOURCE)
    private @interface Mode {

    }

    private final Paint mPathPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint mTextPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Path mRulerPath = new Path();

    private static final long PATH_TIME_DURATION_MILLIS = 1000;

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
    private Drawable mPointerDrawable;
    private float mPointerDrawableWidth = -1;

    @ColorInt
    private int mRulerColor = Color.WHITE;
    @ColorInt
    private int mWaveColor = Color.WHITE;

    //state
    private float mPointerPositionX;
    @Mode
    private int mMode;

    // Motion
    private final GestureDetector mGestureDetector;
    private final OverScroller mGestureScroller;

    private float mWaveScrollX;
    private int mScrollXInitialOffset;

    // MARK: data
    private RulerAdapter mRulerAdapter;
    private LayoutStrategy mLayoutStrategy;

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
        mGestureScroller = new OverScroller(context);

        if (isInEditMode()) {
            initFakeData();
        }
    }

    public RulerAdapter getRulerAdapter() {
        return mRulerAdapter;
    }

    public void setRulerAdapter(RulerAdapter rulerAdapter) {
        mRulerAdapter = rulerAdapter;
        rulerAdapter.setView(this);

        notifyDataSetChanged();
    }

    public float getRulerHeight() {
        return mRulerHeight;
    }

    public LayoutStrategy getLayoutStrategy() {
        return mLayoutStrategy;
    }

    public void setLayoutStrategy(LayoutStrategy layoutStrategy) {
        mLayoutStrategy = layoutStrategy;
    }

    public void setRulerHeight(float rulerHeight) {
        mRulerHeight = rulerHeight;
    }

    public float getRulerSecondaryHeight() {
        return mRulerSecondaryHeight;
    }

    public void setRulerSecondaryHeight(float rulerSecondaryHeight) {
        mRulerSecondaryHeight = rulerSecondaryHeight;
    }

    public float getRulerSecondWidth() {
        return mRulerSecondWidth;
    }

    public void setRulerSecondWidth(float rulerSecondWidth) {
        mRulerSecondWidth = rulerSecondWidth;
    }

    public int getRulerPrecision() {
        return mRulerPrecision;
    }

    public void setRulerPrecision(int rulerPrecision) {
        mRulerPrecision = rulerPrecision;
    }

    public float getRulerTextPadding() {
        return mRulerTextPadding;
    }

    public void setRulerTextPadding(float rulerTextPadding) {
        mRulerTextPadding = rulerTextPadding;
    }

    public int getWaveScalePrecision() {
        return mWaveScalePrecision;
    }

    public void setWaveScalePrecision(int waveScalePrecision) {
        mWaveScalePrecision = waveScalePrecision;
    }

    public float getWaveStrokeWidth() {
        return mWaveStrokeWidth;
    }

    public void setWaveStrokeWidth(float waveStrokeWidth) {
        mWaveStrokeWidth = waveStrokeWidth;
    }

    public float getRulerStrokeWidth() {
        return mRulerStrokeWidth;
    }

    public void setRulerStrokeWidth(float rulerStrokeWidth) {
        mRulerStrokeWidth = rulerStrokeWidth;
    }

    public int getRulerColor() {
        return mRulerColor;
    }

    public void setRulerColor(@ColorInt int rulerColor) {
        mRulerColor = rulerColor;
    }

    public void setTextColor(@ColorInt int textColor) {
        mTextPaint.setColor(textColor);
    }

    @ColorInt
    public int getTextColor() {
        return mTextPaint.getColor();
    }

    public void setTextSize(float textSize) {
        mTextPaint.setTextSize(textSize);
    }

    public float getTextSize() {
        return mTextPaint.getTextSize();
    }

    public int getWaveColor() {
        return mWaveColor;
    }

    public void setWaveColor(int waveColor) {
        mWaveColor = waveColor;
    }

    public float getPointerPositionX() {
        return mPointerPositionX;
    }

    public void setPointerPositionX(float pointerPositionX) {
        mPointerPositionX = pointerPositionX;
    }

    public Drawable getPointerDrawable() {
        return mPointerDrawable;
    }

    public void setPointerDrawable(Drawable pointerDrawable) {
        mPointerDrawable = pointerDrawable;
    }

    public float getPointerDrawableWidth() {
        return mPointerDrawableWidth;
    }

    public void setPointerDrawableWidth(float pointerDrawableWidth) {
        mPointerDrawableWidth = pointerDrawableWidth;
    }

    /**
     * @return one of {@link #MODE_SCROLL_BY_TIME} or {@link #MODE_SCROLL_BY_TOUCH} or {@link #MODE_FOLLOW_NEW_DATA}
     */
    public int getMode() {
        return mMode;
    }

    /**
     * set the interact mode for this view
     *
     * @param mode one of {@link #MODE_SCROLL_BY_TIME} or {@link #MODE_SCROLL_BY_TOUCH} or {@link #MODE_FOLLOW_NEW_DATA}
     *
     * @throws IllegalArgumentException when param invalid
     */
    public void setMode(@Mode int mode) throws IllegalArgumentException {
        if (mode != MODE_SCROLL_BY_TIME && mode != MODE_SCROLL_BY_TOUCH && mode != MODE_FOLLOW_NEW_DATA) {
            throw new IllegalArgumentException(
                    "mode != MODE_SCROLL_BY_TIME && mode != MODE_SCROLL_BY_TOUCH && mode != MODE_FOLLOW_NEW_DATA");
        }
        mMode = mode;
    }

    public int getScrollXInitialOffset() {
        return mScrollXInitialOffset;
    }

    public void setScrollXInitialOffset(int scrollXInitialOffset) {
        mScrollXInitialOffset = scrollXInitialOffset;
    }

    private void initFakeData() {
        mRulerHeight = 50;
        mRulerSecondaryHeight = 15;
        mRulerSecondWidth = 200;
        mRulerPrecision = 4;
        mWaveScalePrecision = 20;
        mWaveStrokeWidth = 2;

        mRulerColor = Color.WHITE;
        mRulerTextPadding = 10;
        mRulerStrokeWidth = 2;

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

        if (mRulerAdapter != null) {
            // draw ruler time text
            float textX = -offset + mRulerTextPadding;
            final float textY = mRulerHeight - mRulerSecondaryHeight - mRulerTextPadding;

            while (textX < getWidth()) {
                CharSequence timeText = getTimeText(startTime);
                if (timeText != null) {
                    canvas.drawText(timeText, 0, timeText.length(), textX, textY, mTextPaint);
                }

                textX += mRulerSecondWidth;
                startTime++;
            }
        }
    }

    private void drawPointer(Canvas canvas) {
        mPathPaint.setStyle(Paint.Style.FILL_AND_STROKE);

        if (mPointerDrawable != null) {
            int dw = mPointerDrawableWidth < 0 ? mPointerDrawable.getIntrinsicWidth() : (int) mPointerDrawableWidth;
            mPointerDrawable.setBounds(0, 0, mPointerDrawable.getIntrinsicWidth(), (int) (getHeight() - mRulerHeight));
            canvas.save();
            canvas.translate(mPointerPositionX - dw / 2, mRulerHeight);
            mPointerDrawable.draw(canvas);
            canvas.restore();
        } else {
            mPathPaint.setColor(Color.RED & 0x66FFFFFF);
            canvas.drawLine(mPointerPositionX, mRulerHeight, mPointerPositionX, getHeight(), mPathPaint);
        }
    }

    @Nullable
    private CharSequence getTimeText(int second) {
        if (mRulerAdapter == null) {
            return null;
        }
        return mRulerAdapter.getTimeString(second);
    }

    /**
     * @return second
     */
    private int getCurrentStartTime() {
        return (int) Math.floor(mWaveScrollX / mRulerSecondWidth);
    }

    private float getCurrentScrollOffset() {
        float offset = mWaveScrollX % mRulerSecondWidth;
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

        if (mLayoutStrategy != null) {
            mLayoutStrategy.onViewSizeChanged(this, w, h);
        }

        constructRulerPath(w, h, oldw, oldh);
        adjustPosition(true, false);
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
                //long ruler
                rulerHeight = mRulerHeight;
            } else {
                //short ruler
                rulerHeight = mRulerSecondaryHeight;
            }

            mRulerPath.rLineTo(0, -rulerHeight);
            mRulerPath.rMoveTo(precision, rulerHeight);
        }
    }

    private void updateWavePath() {
        if (mRulerAdapter == null) {
            recycleAllPathSegment();
            invalidate();
            return;
        }

        final long startTimeMillis = getCurrentStartTime() * 1000;
        final int pathSegmentCountToDisplay =
                (int) Math.ceil((getWidth() + getCurrentScrollOffset()) / mRulerSecondWidth);
        final long endTimeMillis =
                Math.min(startTimeMillis + PATH_TIME_DURATION_MILLIS * pathSegmentCountToDisplay,
                         mRulerAdapter.getTotalTime());
        final long lastSegmentStartTime = endTimeMillis - (1 + (endTimeMillis - 1) % PATH_TIME_DURATION_MILLIS);

        if (getLivePathSegmentsStartTime() == startTimeMillis &&
                getLivePathSegmentsEndTime() == endTimeMillis) {
            // the same
            return;
        }

        if (mLivePathSegments.isEmpty()) {
            addPathSegment(startTimeMillis, endTimeMillis, PATH_TIME_DURATION_MILLIS, true);
        } else {
            addPathSegmentIncrementally(startTimeMillis, PATH_TIME_DURATION_MILLIS, endTimeMillis,
                                        lastSegmentStartTime);
        }

        invalidate();
    }

    private void addPathSegmentIncrementally(
            long startTimeMillis,
            long pathTimeDuration,
            long endTimeMillis,
            long lastSegmentStartTime) {

        // remove too early items
        ListIterator<PathSegment> it = mLivePathSegments.listIterator();
        while (it.hasNext()) {
            PathSegment tmp = it.next();
            if (tmp.startTime < startTimeMillis) {
                recyclePathSegment(tmp);
                it.remove();
            } else {
                break;
            }
        }

        // remove too late items
        it = mLivePathSegments.listIterator(mLivePathSegments.size());
        while (it.hasPrevious()) {
            PathSegment tmp = it.previous();
            if (tmp.startTime > lastSegmentStartTime) {
                recyclePathSegment(tmp);
                it.remove();
            } else {
                break;
            }
        }

        // add or update items
        it = mLivePathSegments.listIterator();
        while (startTimeMillis < endTimeMillis) {
            if (it.hasNext()) {
                PathSegment tmp = it.next();
                if (startTimeMillis < tmp.startTime) {
                    // insert item at front
                    PathSegment newOne = obtainPathSegment();
                    long duration = Math.min(endTimeMillis - startTimeMillis, pathTimeDuration);
                    newOne.constructPath(startTimeMillis, duration);
                    startTimeMillis += duration;

                    it.previous();
                    it.add(newOne);
                } else if (!tmp.partialBuild) {
                    // meet the reusable part, skip it
                    // update time
                    startTimeMillis = tmp.getEndTime();
                } else {
                    // the last one is partial build
                    // update it
                    long duration = Math.min(endTimeMillis - startTimeMillis, pathTimeDuration);
                    tmp.constructPath(startTimeMillis, duration);

                    startTimeMillis += duration;
                }
            } else {
                // reached end, just add new items
                PathSegment tmp = obtainPathSegment();
                long duration = Math.min(endTimeMillis - startTimeMillis, pathTimeDuration);
                tmp.constructPath(startTimeMillis, duration);
                startTimeMillis += duration;

                it.add(tmp);
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

        if (mWaveScrollX > getMaxScroll()) {
            // data deleted on our ruler pointer
            scrollToRight(true);
        }
    }

    public void notifyDataAdded(long startTime, long duration) {
        updateWavePath();

        final float posBeforeChange = timeToScrollOffset(startTime);

        // view is in the old position or fling to the old position
        // scroll to new position automatically
        /*
        Math.abs(posBeforeChange - mWaveScrollX) < mRulerSecondWidth / mWaveScalePrecision
                || (!mGestureScroller.isFinished())
                && mGestureScroller.getStartX() < mGestureScroller.getFinalX()
                && mGestureScroller.getFinalX() + mRulerSecondWidth > posBeforeChange
                */
        if (mMode == MODE_FOLLOW_NEW_DATA) {
            // if the pointer is too far from the right position
            // we just jump to it without any animation
            if (getMaxScroll() - mWaveScrollX > mRulerSecondWidth * 3 / mWaveScalePrecision) {
                scrollToRight(false);
            } else {
                scrollToRight(true);
            }
        }
    }

    private float timeToScrollOffset(long timeMillis) {
        return timeMillis * mRulerSecondWidth / 1000 + mScrollXInitialOffset;
    }

    /**
     * @param position in the view coordinator, ranged [0, getWidth()]
     *
     * @return
     */
    private long positionToTimeMillis(float position) {
        float pos = mWaveScrollX + mScrollXInitialOffset - position;
        return (long) (pos / mRulerSecondWidth * 1000);
    }

    public static abstract class RulerAdapter {
        private AudioTimeRulerView mAudioTimeRulerView;

        public abstract CharSequence getTimeString(long timeSecond);

        public abstract long getTotalTime();

        /**
         * @param timeMillis <em>NOTE: this value may be out of bounds, because of scrolling.</em>
         *
         * @return height of wave ranged [0, 100]
         */
        public abstract int getDataForTime(long timeMillis);

        @Nullable
        public AudioTimeRulerView getView() {
            return mAudioTimeRulerView;
        }

        /*package*/ void setView(@NonNull AudioTimeRulerView view) {
            mAudioTimeRulerView = view;
        }

        public void notifyDataAdded(long startTime, long duration) {
            if (mAudioTimeRulerView != null) {
                mAudioTimeRulerView.notifyDataAdded(startTime, duration);
            }
        }

        public void notifyDataSetChanged() {
            if (mAudioTimeRulerView != null) {
                mAudioTimeRulerView.notifyDataSetChanged();
            }
        }
    }

    public interface LayoutStrategy {
        void onViewSizeChanged(@NonNull AudioTimeRulerView view, int width, int height);
    }

    /**
     * 1 second time wave path.
     */
    private class PathSegment {
        public final Path path = new Path();
        public long startTime;
        public long duration;
        public float totalHeight;
        public float totalWidth;
        public boolean partialBuild;

        public long getEndTime() {
            return startTime + duration;
        }

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
                addWaveToPath(this.duration, startTime + this.duration, duration - this.duration);
                this.duration = duration;
            }

            partialBuild = duration < PATH_TIME_DURATION_MILLIS;
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

            long totalTime = originTime + duration;
            totalWidth = (totalTime + rulerTimeGapMs - 1) / rulerTimeGapMs * rulerXGap;
        }

        public void drawAt(Canvas canvas, float startX, float y) {
            if (mMode == MODE_FOLLOW_NEW_DATA && startX >= mPointerPositionX) {
                // no need to draw
                return;
            }

            mPathPaint.setColor(mWaveColor);
            mPathPaint.setStrokeWidth(mWaveStrokeWidth);

            final boolean isWaveAcrossPointer =
                    startX < mPointerPositionX && startX + totalWidth > mPointerPositionX;
            // in auto follow mode, wave cannot go across the pointer
            final boolean needClip = isWaveAcrossPointer && mMode == MODE_FOLLOW_NEW_DATA;

            final float extra = mWaveStrokeWidth / 2;

            canvas.save();
            canvas.translate(startX + extra, totalHeight + y);

            if (needClip) {
                // do clip
                canvas.clipRect(-extra, -totalHeight, mPointerPositionX - startX, totalHeight);
            }

            // do draw
            canvas.drawPath(path, mPathPaint);

            if (needClip) {
                mPathPaint.setColor(Color.BLUE);
                canvas.drawLine(mPointerPositionX - startX,
                                -totalHeight,
                                mPointerPositionX - startX,
                                totalHeight,
                                mPathPaint);
            }

            if (needClip) {
                canvas.restore();
            }

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

    /**
     * @return current time the pointer is pointing to
     */
    public long getCurrentTimeMillis() {
        return positionToTimeMillis(mPointerPositionX);
    }

    private float getMaxScroll() {
        if (mRulerAdapter != null) {
            return timeToScrollOffset(mRulerAdapter.getTotalTime());
        }
        return 0;
    }

    public void scrollToTime(long timeMillis, boolean doAnimation) {
        mGestureScroller.forceFinished(true);
        final int destination = (int) timeToScrollOffset(timeMillis);

        if (doAnimation) {
            mGestureScroller.startScroll(
                    (int) mWaveScrollX, 0,
                    (int) (destination - mWaveScrollX), 0);
        } else {
            mWaveScrollX = destination;
        }

        invalidate();
    }

    public void scrollToLeft(boolean doAnimation) {
        scrollToTime(0, doAnimation);
    }

    public void scrollToRight(boolean doAnimation) {
        scrollToTime(mRulerAdapter != null ? mRulerAdapter.getTotalTime() : 0, doAnimation);
    }

    private void adjustPosition(boolean forceAdjust, boolean doAnimation) {
        if (!mGestureScroller.isFinished()) {
            if (forceAdjust) {
                // abort current scrolling
                mGestureScroller.abortAnimation();
            } else {
                // do nothing when scrolling
                return;
            }
        }

        boolean needAdjust = forceAdjust;
        int targetScroll = mScrollXInitialOffset;
        final float maxScroll;

        if (mWaveScrollX < mScrollXInitialOffset) {
            targetScroll = mScrollXInitialOffset;
            needAdjust = true;
        } else if (mWaveScrollX > (maxScroll = getMaxScroll())) {
            targetScroll = (int) maxScroll;
            needAdjust = true;
        }

        if (needAdjust) {
            if (doAnimation) {
                mGestureScroller.startScroll(
                        (int) mWaveScrollX, 0,
                        (int) (targetScroll - mWaveScrollX), 0);
            } else {
                mWaveScrollX = targetScroll;
            }
            invalidate();
        }
    }

    // Mark: Gesture and scroll
    @Override
    public void scrollTo(int x, int y) {
        mGestureScroller.startScroll((int) mWaveScrollX, 0, x, 0);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (mMode == MODE_SCROLL_BY_TOUCH) {
            boolean consumed = mGestureDetector.onTouchEvent(event);
            if (event.getActionMasked() == MotionEvent.ACTION_UP
                    || event.getActionMasked() == MotionEvent.ACTION_CANCEL) {
                adjustPosition(false, true);
                return true;
            }
            return consumed;
        } else {
            return false;
        }
    }

    @Override
    public void computeScroll() {
        super.computeScroll();

        if (mGestureScroller.computeScrollOffset()) {
            mWaveScrollX = mGestureScroller.getCurrX();
            invalidate();
        }
    }

    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
        // stop previous anime
        mGestureScroller.abortAnimation();

        mWaveScrollX += distanceX;

        invalidate();
        return true;
    }

    @Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        // stop previous anime
        mGestureScroller.abortAnimation();

        mGestureScroller.fling(
                (int) mWaveScrollX, 0,
                (int) -velocityX, 0,
                //min/max X
                mScrollXInitialOffset, (int) getMaxScroll(),
                0, 0,
                (int) mRulerSecondWidth, 0);

        invalidate();
        return true;
    }

    @Override
    public boolean onDown(MotionEvent e) {
        mGestureScroller.abortAnimation();
        return true;
    }

    @Override
    public void onShowPress(MotionEvent e) {

    }

    @Override
    public boolean onSingleTapUp(MotionEvent e) {
        if (mGestureScroller.isFinished()) {
            if (mWaveScrollX < mScrollXInitialOffset) {
                mGestureScroller.startScroll(
                        (int) mWaveScrollX, 0,
                        (int) (mScrollXInitialOffset - mWaveScrollX), 0);
            } else {
                float maxScrollX = 0;
                if (mRulerAdapter != null) {
                    maxScrollX = mRulerAdapter.getTotalTime() * mRulerSecondWidth / 1000;
                }
                if (mWaveScrollX > maxScrollX) {
                    mGestureScroller.startScroll((int) maxScrollX, 0,
                                                 (int) (maxScrollX - mWaveScrollX), 0);
                }
            }
        }
        return true;
    }

    @Override
    public void onLongPress(MotionEvent e) {

    }

    @Override
    protected boolean verifyDrawable(Drawable who) {
        return super.verifyDrawable(who) || who == mPointerDrawable;
    }
}