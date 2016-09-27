package com.young.jnirawbytetest.audiotest;


import io.github.landerlyoung.jenny.NativeClass;

/**
 * Author: landerlyoung@gmail.com
 * Date:   2016-08-19
 * Time:   15:53
 * Life with Passion, Code with Creativity.
 */
@NativeClass
public class KalaMix {
    private long mNativeHandel;

    public KalaMix(int sampleRate, int bgmChannelCount, int vocalChannelCount) {
        mNativeHandel = create(sampleRate, bgmChannelCount, vocalChannelCount);
    }

    public int process(byte[] bgm, int bgmSize, byte[] vocal, int vocalSize, byte[] out, int outSize) {
        return process(mNativeHandel, bgm, bgmSize, vocal, vocalSize, out, outSize);
    }

    public void release() {
        release(mNativeHandel);
        mNativeHandel = 0;
    }

    private static native long create(int sampleRate,int bgmChannelCount, int vocalChannelCount);

    private static native int process(long handel, byte[] bgm, int bgmSize, byte[] vocal, int vocalSize, byte[] out, int outSize);

    private native void release(long handel);
}
