package com.young.jnirawbytetest;

import android.support.annotation.NonNull;

import com.young.jenny.annotation.NativeClass;
import com.young.jenny.annotation.NativeCode;

import java.nio.ByteBuffer;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-04
 * Time:   13:22
 * Life with Passion, Code with Creativity.
 */
@NativeClass
public class CppSide {
    static {
        System.loadLibrary("native-lib");
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
            "std::memset(arr, sizeof(jbyte), length);",
            "env->ReleaseByteArrayElements(data, arr, JNI_COMMIT);",
            "LOGV(\"GetByteArrayElements isCopy %s\", (isCopy ? \"true\" : \"false\"));",
    })
    public static native void passByteArrayToNative(@NonNull byte[] data);

    /**
     * pass an empty DirectByteBuffer to native, and fill with 1.
     *
     * @param data
     */
    @NativeCode({
            "jbyte *arr = static_cast<jbyte *>(env->GetDirectBufferAddress(data));",
            "jlong length = env->GetDirectBufferCapacity(data);",
            "std::memset(arr, sizeof(jbyte), length);"
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
}
