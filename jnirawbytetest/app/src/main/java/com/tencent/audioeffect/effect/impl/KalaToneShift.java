package com.tencent.audioeffect.effect.impl;


import io.github.landerlyoung.jenny.NativeClass;

/**
 * Author: landerlyoung@gmail.com
 * Date:   2016-08-25
 * Time:   22:12
 * Life with Passion, Code with Creativity.
 */
@NativeClass
public class KalaToneShift {

    private long mNativeHandel;

    public KalaToneShift(int sampleRate, int channelCount) {
        mNativeHandel = nativeCreate(sampleRate, channelCount);
    }

    /** @param shiftVal [-12, +12] */
    public int setShiftValue(int shiftVal) {
        return setShiftValue(mNativeHandel, shiftVal);
    }

    public int process(byte[] inBuf, int inSize,
                       byte[] outBuf, int outSize) {
        return process(mNativeHandel, inBuf, inSize, outBuf, outSize);
    }

    public void release() {
        release(mNativeHandel);
        mNativeHandel = 0;
    }

    private static native long nativeCreate(int sampleRate, int channelCount);

    private static native int setShiftValue(long handle, int shiftVal);

    private static native int process(long handel,
                                      byte[] inBuf, int inSize,
                                      byte[] outBuf, int outSize);

    private static native void release(long handle);
}
