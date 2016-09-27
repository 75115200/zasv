package com.tencent.component.media.effect;

import android.support.annotation.NonNull;
import android.util.Log;

import io.github.landerlyoung.jenny.NativeClass;

/**
 * <pre>
 * Author: landerlyoung@gmail.com
 * Date:   2016-09-21
 * Time:   17:00
 * Life with Passion, Code with Creativity.
 * </pre>
 */
@NativeClass
public class VoiceChangerWrapper {
    private static final String TAG = "VoiceChangerWrapper";

    static {
        System.loadLibrary("radio_effect");
    }

    private static final int OUT_BUFFER_TO_SMALL_MASK = 1 << 31;

    private long mNativeHandel;
    private int mSampleRate;
    private int mChannelCount;
    /**
     * ranged (0, 2]
     */
    private float mSpeedScale = 1.0f;

    private byte[] mNiceOutBuffer;

    //make it big enough
    //other wise native crash will happen
    private int mOutBufferSizeMultiplier = 4;

    public VoiceChangerWrapper() {
        mNativeHandel = nativeCreate();
    }

    public boolean nativeSetParam(int sampleRate, int channelCount, float speedScale) {
        if (speedScale <= 0 || speedScale > 2.5f) {
            return false;
        }
        if (sampleRate != mSampleRate
                || mChannelCount != channelCount
                || mSpeedScale != speedScale) {
            mSampleRate = sampleRate;
            mChannelCount = channelCount;
            mSpeedScale = speedScale;
            nativeSetParam(mNativeHandel, sampleRate, channelCount,
                           (speedScale - 1f) * 100, 0, 0, -1);
        }
        return true;
    }

    /**
     * VoiceChanger底层用的是SoundTouch, 它并非一个实时音频处理程序。
     * 所以可能出现连续input 1k数据, 同时获取数据
     * <p>
     * 出现获取数据的长度 波动很大。
     * 所以我们需要一个足够大的buffer来容纳输出的数据!
     *
     * @param inDataLen
     *
     * @return
     */
    private int getEstimatedOutBufferLength(int inDataLen) {
        int outLen = (int) (inDataLen / mSpeedScale);
        //add some padding
        outLen *= mOutBufferSizeMultiplier;
        return outLen;
    }

    /**
     * get a buffer long enough to hold the out data
     */
    @NonNull
    public byte[] getNiceOutBuffer(int inDataLen) {
        int len = getEstimatedOutBufferLength(inDataLen);
        if (mNiceOutBuffer == null || mNiceOutBuffer.length < len) {
            mNiceOutBuffer = new byte[len];
        }
        return mNiceOutBuffer;
    }

    private void nativeSetParam(
            int sampleRate, int channel,
            float tempoDelta, float pitchDelta,
            int voiceKind, int environment) {
        nativeSetParam(mNativeHandel,
                       sampleRate, channel,
                       tempoDelta, pitchDelta,
                       voiceKind, environment);
    }

    public int process(byte[] inPcmData, int inPcmLen, byte[] outPcmData, int outPcmLen) {
        int outLengthMasked = nativeProcess(mNativeHandel, inPcmData, inPcmLen, outPcmData, outPcmLen);
        if ((outLengthMasked & OUT_BUFFER_TO_SMALL_MASK) != 0) {
            //out buffer too small
            mOutBufferSizeMultiplier++;
            Log.e(TAG, "process: outBufferLen:" + outPcmLen + " is TOO SMALL!"
                    + " adjust OutBufferSizeMultiplier to " + mOutBufferSizeMultiplier);

            //remove mask
            return outLengthMasked & (~outLengthMasked);
        } else {
            return outLengthMasked;
        }
    }

    public void release() {
        if (mNativeHandel != 0) {
            nativeRelease(mNativeHandel);
            mNativeHandel = 0;
        }
    }

    @Override
    protected void finalize() throws Throwable {
        super.finalize();
        release();
    }

    /**
     * return 0 for failure
     *
     * @return
     */
    private native static long nativeCreate();

    private native void nativeSetParam(
            long nativeHandel,
            int sampleRate, int channel,
            float tempoDelta, float pitchDelta,
            int voiceKind, int environment
    );

    /**
     * @param nativeHandel
     * @param inData
     * @param inDatasize
     * @param outData
     * @param outDatasize
     *
     * @return OutLengthMasked = outLength | {@link #OUT_BUFFER_TO_SMALL_MASK}
     */
    private native int nativeProcess(long nativeHandel, byte[] inData, int inDatasize, byte[] outData, int outDatasize);

    private native void nativeRelease(long nativeHandel);
}
