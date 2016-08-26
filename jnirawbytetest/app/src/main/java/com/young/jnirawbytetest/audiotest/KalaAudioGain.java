package com.young.jnirawbytetest.audiotest;

import com.young.jenny.annotation.NativeClass;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-26
 * Time:   11:27
 * Life with Passion, Code with Creativity.
 */
@NativeClass
public class KalaAudioGain {
    private long mNativeHandel;

    public  KalaAudioGain(int sampleRate, int channelCount) {
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
