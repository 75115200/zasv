package com.young.jnirawbytetest.audiotest;


import io.github.landerlyoung.jenny.NativeClass;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-26
 * Time:   11:27
 * Life with Passion, Code with Creativity.
 * <hr>
 * crash on stereo audio
 */
@NativeClass
public class KalaAudioGain {
    private long mNativeHandel;

    /**
     * @param sampleRate
     * @param channelCount only support mono channel audio
     */
    public  KalaAudioGain(int sampleRate, int channelCount) {
        if (channelCount != 1) {
            throw new IllegalArgumentException("only support mono channel audio");
        }
        mNativeHandel = create(sampleRate, channelCount);
    }

    public int process(byte[] inOutBuffer, int size) {
        return process(mNativeHandel, inOutBuffer, size);
    }

    public void release() {
        release(mNativeHandel);
        mNativeHandel = 0;
    }

    private static native long create(int sampleRate, int channelCount);

    private static native int process(long nativeHandel, byte[] inOutBuffer, int size);

    private static native void release(long nativeHandel);
}
