package com.tencent.radio.ugc.record.widget;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.support.annotation.ColorInt;
import android.support.annotation.NonNull;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Scroller;


import java.util.Formatter;
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
    private final Path mWavePath = new Path();

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
    private int mScalePrecision;

    private float mRulerStrokeWidth;
    private float mPointerStrokeWidth;
    private float mPointerTriangleWidth;

    @ColorInt
    private int mRulerColor = Color.WHITE;
    @ColorInt
    private int mPointerColor = Color.WHITE;

    private float mScaleStepWidth;
    private float mScaleStrokeWidth;

    //state
    private float mPointerPositionX;

    //text display
    private StringBuilder mCachedTimeTextStingBuilder = new StringBuilder();
    private Formatter mCachedTimeTextFormatter = new Formatter(mCachedTimeTextStingBuilder, Locale.US);

    // Motion
    private final GestureDetector mGestureDetector;
    private final Scroller mScroller;



    public AudioTimeRulerView(Context context) {
        this(context, null);
    }

    public AudioTimeRulerView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public AudioTimeRulerView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);

        mGestureDetector = new GestureDetector(context, this);
        mScroller = new Scroller(context);

        initFakeData();
    }

    private void initFakeData() {
        mRulerHeight = 50;
        mRulerSecondaryHeight = 15;
        mRulerSecondWidth = 200;
        mRulerPrecision = 4;
        mScalePrecision = 20;

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

        drawPointer(canvas);

        drawWave(canvas);

    }

    private void drawPointer(Canvas canvas) {
        canvas.save();
        canvas.translate(mPointerPositionX, mRulerHeight);
        mPathPaint.setStyle(Paint.Style.FILL_AND_STROKE);
        mPathPaint.setStrokeWidth(mPointerStrokeWidth);
        mPathPaint.setColor(mPointerColor);
        canvas.drawPath(mPointerPath, mPathPaint);
        canvas.restore();
    }

    private void drawRuler(Canvas canvas) {
        // draw time
        int startTime = getCurrentStartTime();
        float offset = getCurrentStartOffset();

        mPathPaint.setStyle(Paint.Style.STROKE);
        mPathPaint.setColor(mRulerColor);
        mPathPaint.setStrokeWidth(mRulerStrokeWidth);

        // draw ruler line
        canvas.save();
        canvas.translate(offset, 0);
        canvas.drawPath(mRulerPath, mPathPaint);
        canvas.restore();

        // draw ruler time test
        float textX = offset + mRulerTextPadding;
        final float textY = mRulerHeight - mRulerSecondaryHeight - mRulerTextPadding;

        while (textX < getWidth()) {
            CharSequence timeText = getTimeText(startTime);
            canvas.drawText(timeText, 0, timeText.length(), textX, textY, mTextPaint);

            textX += mRulerSecondWidth;
            startTime++;
        }
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
        int offset = -getScrollX();
        int time = (int) (offset / mRulerSecondWidth);

        return time;
    }

    private float getCurrentStartOffset() {
        int leftMoved = (int) (getScrollX() % mRulerSecondWidth);

        return -leftMoved;
    }

    private void drawWave(Canvas canvas) {

    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        constructRulerPath(w, h, oldw, oldh);
        constructPointerPath(w, h, oldw, oldh);

        mPointerPositionX = w / 2;
    }

    private void constructRulerPath(int width, int height, int oldWidth, int oldHeight) {
        if (width == oldWidth) return;

        mRulerPath.rewind();
        mRulerPath.moveTo(0, mRulerHeight);
        mRulerPath.lineTo(getWidth() + mRulerSecondWidth, mRulerHeight);

        final int linesToDraw = 1 + (int) (width / mRulerSecondWidth * mRulerPrecision);
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

    private void constructWavePath() {

    }


    // Mark: Gesture


    @Override
    public void computeScroll() {
        super.computeScroll();
        if (mScroller.computeScrollOffset()) {
            int x = mScroller.getCurrX();
            scrollTo(x, 0);
            invalidate();
        }
    }

    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
        mScroller.startScroll(getScrollX(), getScrollY(), (int) distanceX, getScrollY());

        return false;
    }

    @Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        mScroller.fling(getScrollX(), getScrollY(), (int) velocityX, 0,
                        /*minX*/ 0,
                        //todo fix maxX
                        /*maxX*/ 1000,
                        0, 0);
        return false;
    }

    @Override
    public boolean onDown(MotionEvent e) {
        return false;
    }

    @Override
    public void onShowPress(MotionEvent e) {

    }

    @Override
    public boolean onSingleTapUp(MotionEvent e) {
        return false;
    }

    @Override
    public void onLongPress(MotionEvent e) {

    }

}
