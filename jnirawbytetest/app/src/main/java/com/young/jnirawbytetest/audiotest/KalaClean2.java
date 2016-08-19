package com.young.jnirawbytetest.audiotest;

import com.young.jenny.annotation.NativeClass;
import com.young.jenny.annotation.NativeCode;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-19
 * Time:   14:47
 * Life with Passion, Code with Creativity.
 */
@NativeClass
public class KalaClean2 {
    private long mNativeHandel;

    public KalaClean2(int sampleRate, int channel) {
        mNativeHandel = createClean2(sampleRate, channel);
    }

    public int process(byte[] inBuffer, int size) {
        return clean2Process(mNativeHandel, inBuffer, size);
    }

    public void destroy() {
        destroyClean2(mNativeHandel);
        mNativeHandel = 0;
    }

    @NativeCode({
            "CCleanNew3* ins = new CCleanNew3();",
            "ins->Init(sampleRate, channel);",
            "return reinterpret_cast<jlong>(ins);"
    })
    private static native long createClean2(int sampleRate, int channel);

    @NativeCode({
            "CCleanNew3 *ins = reinterpret_cast<CCleanNew3 *>(handel);",
            "jboolean isCopy;",
            "jbyte *buffer = env->GetByteArrayElements(inBuffer, &isCopy);",
            "jint ret = ins->Process(reinterpret_cast<char*>(buffer), size);",
            "env->ReleaseByteArrayElements(inBuffer, buffer, 0);",
            "return ret;",
    })
    private static native int clean2Process(long handel, byte[] inBuffer, int size);

    @NativeCode({
            "CCleanNew3* ins = reinterpret_cast<CCleanNew3*>(handel);",
            "ins->Uninit();",
            "delete ins;",
    })
    private native void destroyClean2(long handel);
}

