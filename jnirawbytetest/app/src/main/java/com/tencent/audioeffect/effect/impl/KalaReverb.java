package com.tencent.audioeffect.effect.impl;

import io.github.landerlyoung.jenny.NativeClass;

/**
 * Author: landerlyoung@gmail.com
 * Date:   2016-08-29
 * Time:   16:45
 * Life with Passion, Code with Creativity.
 */
//crash on mono audio
@NativeClass
public class KalaReverb {
    //keep in sync with CReverb4.h

    /** no effect */
    public static final int KALA_VB_NO_EFFECT_QUICKLY = 10;
    /** KTV, change to v1.5's ktv . */
    public static final int KALA_VB_KTV_V40_QUICKLY = 11;
    /** warm, wennuan */
    public static final int KALA_VB_WARM_QUICKLY = 12;
    /** magnetic, cixing */
    public static final int KALA_VB_MAGNETIC_QUICKLY = 13;
    /** ethereal, kongling */
    public static final int KALA_VB_ETHEREAL_QUICKLY = 14;
    /** distant, youyuan */
    public static final int KALA_VB_DISTANT_QUICKLY = 15;
    /** dizzy, mihuan */
    public static final int KALA_VB_DIZZY_QUICKLY = 16;
    /** phonograph, laochangpian */
    public static final int KALA_VB_PHONOGRAPH_QUICKLY = 17;
    /** not used, discard. */
    public static final int KALA_VB_PHONOGRAPH_GENERIC_QUICKLY = 18;

    private long mNativeHandel;

    /**
     * @param sampleRate
     * @param channelCount only support stereo channel audio
     */
    public KalaReverb(int sampleRate, int channelCount) {
        if (channelCount != 2) {
//            throw new IllegalArgumentException("only support stereo channel audio");
        }
        mNativeHandel = create(sampleRate, channelCount);
    }


    /**
     * @param maxAndMin getDataOut [max, min]
     */
    public void getIdRange(int[] maxAndMin) {
        getIdRange(mNativeHandel, maxAndMin);
    }

    public int getIdDefault() {
        return getIdDefault(mNativeHandel);
    }

    public int setTypeId(int type) {
        return setTypeId(mNativeHandel, type);
    }

    public int getTypeId() {
        return getTypeId(mNativeHandel);
    }

    public String getNameId(int typeId) {
        return getNameId(mNativeHandel, typeId);
    }

    public int process(byte[] inBuffer, int insize, byte[] outBuffer, int outSize) {
        process(mNativeHandel, inBuffer, insize, outBuffer, outSize);
        return insize;
    }

    public void release() {
        if (mNativeHandel != 0) {
            release(mNativeHandel);
            mNativeHandel = 0;
        }
    }


    private static native long create(int sampleRate, int channelCount);

    private static native void getIdRange(long nativeHandel, int[] maxAndMin);

    private static native int getIdDefault(long nativeHandel);

    private static native int setTypeId(long nativeHandel, int type);

    private static native int getTypeId(long nativeHandel);

    private static native String getNameId(long nativeHandel, int typeId);

    private static native int process(long nativeHandel, byte[] inBuffer, int insize, byte[] outBuffer, int outSize);

    private static native void release(long nativeHandel);

}
