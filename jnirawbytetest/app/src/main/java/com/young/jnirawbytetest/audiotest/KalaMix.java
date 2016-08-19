package com.young.jnirawbytetest.audiotest;

import com.young.jenny.annotation.NativeClass;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-19
 * Time:   15:53
 * Life with Passion, Code with Creativity.
 */
@NativeClass
public class KalaMix {
    private long mNativeHandel;

    public KalaMix(int sampleRate, int channel) {
        mNativeHandel = create(sampleRate, channel);
    }

    public int process(byte[] bgm, int bgmSize, byte[] vocal, int vocalSize, byte[] out, int outSize) {
        return process(mNativeHandel, bgm, bgmSize, vocal, vocalSize, out, outSize);
    }

    public void release() {
        release(mNativeHandel);
        mNativeHandel = 0;
    }

    private static native long create(int sampleRate, int channel);

    private static native int process(long handel, byte[] bgm, int bgmSize, byte[] vocal, int vocalSize, byte[] out, int outSize);

    private native void release(long handel);
}
