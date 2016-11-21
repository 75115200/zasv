package com.tencent.audioeffect.effect.impl;


import io.github.landerlyoung.jenny.NativeClass;

/**
 * Author: landerlyoung@gmail.com
 * Date:   2016-08-23
 * Time:   15:18
 * Life with Passion, Code with Creativity.
 */
@NativeClass
public class KalaVoiceShift {

    /** Original (No Effect) */
    public static final int KALA_VOICE_SHIFT_NO_EFFECT = 0;
    /** Soprano */
    public static final int KALA_VOICE_SHIFT_SOPRANO = 1;
    /** Basso */
    public static final int KALA_VOICE_SHIFT_BASSO = 2;
    /** Baby */
    public static final int KALA_VOICE_SHIFT_BABY = 3;
    /** Autotune */
    public static final int KALA_VOICE_SHIFT_AUTOTUNE = 4;
    /** metal */
    public static final int KALA_VOICE_SHIFT_METAL = 5;
    /** chorus */
    public static final int KALA_VOICE_SHIFT_CHORUS = 6;

    private long mNativeHandel;

    public KalaVoiceShift(int sampleRate, int channel) {
        mNativeHandel = create(sampleRate, channel);
    }

    /**
     * @param outMaxIdAndMinId int array of length 2, return {maxId, minId}
     */
    public int getIdRange(int[] outMaxIdAndMinId) {
        return getIdRange(mNativeHandel, outMaxIdAndMinId);
    }

    public int getIdDefault() {
        return getIdDefault(mNativeHandel);
    }

    public int setTypeId(int typeId) {
        return setTypeId(mNativeHandel, typeId);
    }

    public int getTypeId() {
        return getTypeId(mNativeHandel);
    }

    public String getNameById(int typeId) {
        return getNameById(mNativeHandel, typeId);
    }

    public int process(byte[] inBuffer, int inSize, byte[] outBuffer, int outBufferSize) {
        return process(mNativeHandel, inBuffer, inSize, outBuffer, outBufferSize);
    }

    public void release() {
        release(mNativeHandel);
        mNativeHandel = 0;
    }

    //==================native methods======================
    private static native long create(int sampleRate, int channel);

    /**
     * @param nativeHandel
     * @param inBuffer
     * @param inSize
     * @param outBuffer
     * @param outBufferSize outBuffer.length
     *
     * @return data written in outBuffer
     */
    private static native int process(long nativeHandel,
                                      byte[] inBuffer, int inSize,
                                      byte[] outBuffer, int outBufferSize);

    private static native int getIdRange(long nativeHandel, int[] outMaxIdAndMinId);

    private static native int getIdDefault(long nativeHandel);

    private static native int setTypeId(long nativeHandel, int typeId);

    private static native int getTypeId(long nativeHandel);

    private static native String getNameById(long nativeHandel, int typeId);

    private static native void release(long nativeHandel);

}
