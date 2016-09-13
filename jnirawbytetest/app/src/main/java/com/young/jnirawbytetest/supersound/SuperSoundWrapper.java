package com.young.jnirawbytetest.supersound;

import android.support.annotation.NonNull;

import io.github.landerlyoung.jenny.NativeClass;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-09-13
 * Time:   17:11
 * Life with Passion, Code with Creativity.
 */
@NativeClass
public class SuperSoundWrapper {
    public enum SUPERSOUND_EFFECT_TYPE {
        SUPERSOUND_NONE_TYPE,            //无音效
        SUPERSOUND_SURROUND_TYPE,        //全景环绕
        SUPERSOUND_BASS_TYPE,            //超重低音
        SUPERSOUND_VOCAL_TYPE,            //清澈人声
        SUPERSOUND_STUDIO_TYPE,            //现场律动
    }

    /**
     * 音效强度范围定义
     * 全景环绕部分
     */
    public static final float SUPERSOUND_SURROUND_PARAM_MIN = (0.0f);
    public static final float SUPERSOUND_SURROUND_PARAM_DEFAUT = (1.3f);
    public static final float SUPERSOUND_SURROUND_PARAM_MAX = (3.0f);

    /** 超重低音部分 */
    public static final float SUPERSOUND_BASS_PARAM_MIN = (0.0f);
    public static final float SUPERSOUND_BASS_PARAM_DEFAUT = (1.5f);
    public static final float SUPERSOUND_BASS_PARAM_MAX = (3.0f);

    /** 清澈人声部分 */
    public static final float SUPERSOUND_VOCAL_PARAM_MIN = (0.0f);
    public static final float SUPERSOUND_VOCAL_PARAM_DEFAUT = (0.1f);
    public static final float SUPERSOUND_VOCAL_PARAM_MAX = (1.5f);

    /** 现场律动部分 */
    public static final float SUPERSOUND_STUDIO_PARAM_MIN = (1.0f);
    public static final float SUPERSOUND_STUDIO_PARAM_DEFAUT = (1.5f);
    public static final float SUPERSOUND_STUDIO_PARAM_MAX = (2.0f);

    private long mNativeHandel;
    private final int mSampleRate;
    private final int mChannelCound;

    static {
        System.loadLibrary("audio_test");
        nativeInit();
    }

    public SuperSoundWrapper(int sampleRate, int channelCount) {
        mChannelCound = channelCount;
        mSampleRate = sampleRate;
        mNativeHandel = nativeCreateIns(sampleRate, channelCount);
    }

    public boolean setIntensity(@NonNull SUPERSOUND_EFFECT_TYPE effect_type, float intensity) {
        return nativeSetIntensity(mNativeHandel, effect_type.ordinal(), intensity);
    }

    public boolean process(@NonNull byte[] data, int sampleCount) {
        return process(mNativeHandel, data, sampleCount);
    }

    public int getLookAhead() {
        return getLookAhead(mNativeHandel);
    }

    public void release() {
        if (mNativeHandel!=0) {
            nativeDestroyIns(mNativeHandel);
            mNativeHandel = 0;
        }
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        release();
    }

    private static native boolean nativeInit();

    private static native boolean nativeUninit();

    private static native long nativeCreateIns(int sampleRate, int channelCound);

    private static native boolean nativeSetIntensity(
            long nativeHandel, int effectType, float intensity);

    private static native int getLookAhead(long nativeHandel);

    private static native boolean processF(
            long nativeHandel, float[] data, int sampleNum);

    private static native boolean process(
            long nativeHandel, byte[] data, int sampleNum);

    private static native boolean nativeDestroyIns(long nativeHandel);
}
