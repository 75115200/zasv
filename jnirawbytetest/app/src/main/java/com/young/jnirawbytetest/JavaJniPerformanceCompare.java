package com.young.jnirawbytetest;

import android.support.annotation.NonNull;


import java.nio.ByteBuffer;

import io.github.landerlyoung.jenny.NativeClass;
import io.github.landerlyoung.jenny.NativeCode;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-04
 * Time:   13:22
 * Life with Passion, Code with Creativity.
 */
@NativeClass
public class JavaJniPerformanceCompare {
    static {
        System.loadLibrary("native_lib");
    }

    public static int javaAdd(int a, int b) {
        return a + b;
    }

    public static int javaBatchAdd(int a, int b, int count) {
        int c = 0;
        for (int i = 0; i < count; i++) {
            c += a + b;
        }
        return c;
    }

    @NativeCode("return a + b;")
    public static native int add(int a, int b);

    @NativeCode({
            "jint c = 0;",
            "for (jint i = 0; i < count; ++i) {",
            "   c += a + b;",
            "}",
            "return c;"
    })
    public static native int batchAdd(int a, int b, int count);

    /**
     * pass 0 write 1 and return
     *
     * @param data
     */
    @NativeCode({
            "jboolean isCopy;",
            "const jint length = env->GetArrayLength(data);",
            "jbyte *arr = env->GetByteArrayElements(data, &isCopy);",
            "std::memset(arr, 1, length);",
            "env->ReleaseByteArrayElements(data, arr, 0);",
            "LOGV(\"GetByteArrayElements isCopy %s\", (isCopy ? \"true\" : \"false\"));",
    })
    public static native void passByteArrayToNative(@NonNull byte[] data);

    /**
     * pass 0 write 1 and return
     *
     * @param data
     */
    @NativeCode({
            "jboolean isCopy;",
            "const jint length = env->GetArrayLength(data);",
            "jshort *arr = env->GetShortArrayElements(data, &isCopy);",
            "jshort s = arr[0];",
            "env->ReleaseShortArrayElements(data, arr, 0);",
            "LOGV(\"GetShortArrayElements isCopy %s h:%d l:%d\", (isCopy ? \"true\" : \"false\"), (0xff00 & s), (0x00ff & s));",
    })
    public static native void testEndianess(@NonNull short[] data);

    /**
     * pass an empty DirectByteBuffer to native, and fill with 1.
     *
     * @param data
     */
    @NativeCode({
            "jbyte *arr = static_cast<jbyte *>(env->GetDirectBufferAddress(data));",
            "jlong length = env->GetDirectBufferCapacity(data);",
            "std::memset(arr, 1, length);"
    })
    public static native void passByteBufferToNative(@NonNull ByteBuffer data);

    @NativeCode({
            "char *src = new char[size];",
            "char *dst = new char[size];",
            "for (int i = 0; i < count; i++) {",
            "   std::memcpy(dst, src, size);",
            "}",
            "delete[] src; delete[] dst;",
    })
    public static native void cppBatchMemcpy(int size, int count);

    public static void javaBatchMemcpy(int size, int count) {
        byte[] src = new byte[size];
        byte[] dst = new byte[size];

        for (int i = 0; i < count; i++) {
            System.arraycopy(src, 0, dst, 0, size);
        }
    }

    @NativeCode({
            "char *data = new char[size];",
            "for (int i = 0; i < count; i++) {",
            "   std::memset(data, 1, size);",
            "}",
            "delete[] data;",
    })
    public static native void cppBatchMemset(int size, int count);

    public static void javaBatchMemset(int size, int count) {
        byte[] data = new byte[size];
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < size; j++) {
                data[j] = (byte) 1;
            }
        }
    }

}
