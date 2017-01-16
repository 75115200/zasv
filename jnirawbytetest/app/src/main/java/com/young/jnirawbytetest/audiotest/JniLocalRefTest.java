package com.young.jnirawbytetest.audiotest;

import android.support.annotation.NonNull;

import io.github.landerlyoung.jenny.NativeClass;

/**
 * <pre>
 * Author: taylorcyang@tencent.com
 * Date:   2017-01-13
 * Time:   14:53
 * Life with Passion, Code with Creativity.
 * </pre>
 */
@NativeClass
public class JniLocalRefTest {
    static {
        System.loadLibrary("audio_test");
    }
    public static native String process(@NonNull Object... arr);
}
