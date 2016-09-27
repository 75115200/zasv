package com.tencent.audioeffect.effect;

import io.github.landerlyoung.jenny.NativeClass;

/**
 * Author: landerlyoung@gmail.com
 * Date:   2016-08-29
 * Time:   16:45
 * Life with Passion, Code with Creativity.
 */
@NativeClass
public class KalaVolumeScaler {
    private long mNativeHandel;

    private int mScaleFactor = 100;

    public KalaVolumeScaler(int sampleRate, int channelCount) {
        mNativeHandel = create(sampleRate, channelCount);
    }

    public int getScaleFactor() {
        return mScaleFactor;
    }

    /**
     * @param scaleFactor ranged [0, 200]. 100 for no change.
     */
    public void setScaleFactor(int scaleFactor) {
        if (scaleFactor != mScaleFactor) {
            setScaleFactor(mNativeHandel, scaleFactor);
        }
    }

    public int process(byte[] inOutData, int size) {
        process(mNativeHandel, inOutData, size);
        return size;
    }

    public void release() {
        if (mNativeHandel != 0) {
            release(mNativeHandel);
            mNativeHandel = 0;
        }
    }

    private static native long create(int sampleRate, int channelCount);

    private static native int setScaleFactor(long nativeHandel, int factor);

    private static native int process(long nativeHandel, byte[] inOutBuffer, int size);

    private static native void release(long nativeHandel);
}
