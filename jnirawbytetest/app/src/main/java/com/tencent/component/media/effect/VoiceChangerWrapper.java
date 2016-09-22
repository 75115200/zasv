package com.tencent.component.media.effect;

import android.support.annotation.NonNull;

import io.github.landerlyoung.jenny.NativeClass;

/**
 * <pre>
 * Author: taylorcyang@tencent.com
 * Date:   2016-09-21
 * Time:   17:00
 * Life with Passion, Code with Creativity.
 * </pre>
 */
@NativeClass
public class VoiceChangerWrapper {
    static {
        System.loadLibrary("radio_effect");
    }

    private long mNativeHandel;
    private int mSampleRate;
    private int mChannelCount;
    /**
     * ranged (0, 2]
     */
    private float mSpeedScale = 1.0f;

    private byte[] mNiceOutBuffer;

    public VoiceChangerWrapper() {
        mNativeHandel = nativeCreate();
    }

    public boolean setParam(int sampleRate, int channelCount, float speedScale) {
        if (speedScale <= 0 || speedScale > 2.5f) {
            return false;
        }
        if (sampleRate != mSampleRate
                || mChannelCount != channelCount
                || mSpeedScale != speedScale) {
            mSampleRate = sampleRate;
            mChannelCount = channelCount;
            mSpeedScale = speedScale;
            setParam(mNativeHandel, sampleRate, channelCount,
                     (speedScale - 1f) * 100, 0, 0, -1);
        }
        return true;
    }

    public int getEstimatedOutBufferLength(int inDataLen) {
        int outLen = (int) (inDataLen / mSpeedScale);
        //add some padding
        outLen += 1024;
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

    private void setParam(int sampleRate, int channel,
                          float tempoDelta, float pitchDelta,
                          int voiceKind, int environment) {
        setParam(mNativeHandel,
                 sampleRate, channel,
                 tempoDelta, pitchDelta,
                 voiceKind, environment);
    }

    public int process(byte[] inPcmData, int inPcmLen, byte[] outPcmData, int outPcmLen) {
        return nativeProcess(mNativeHandel, inPcmData, inPcmLen, outPcmData, outPcmLen);
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

    private native void setParam(
            long nativeHandel,
            int sampleRate, int channel,
            float tempoDelta, float pitchDelta,
            int voiceKind, int environment
    );

    private native int nativeProcess(long nativeHandel, byte[] inData, int inDatasize, byte[] outData, int outDatasize);

    private native void nativeRelease(long nativeHandel);
}
