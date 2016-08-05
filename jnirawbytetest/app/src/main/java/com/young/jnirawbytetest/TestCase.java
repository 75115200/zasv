package com.young.jnirawbytetest;

import android.os.Build;
import android.support.annotation.NonNull;
import android.util.Log;

import java.nio.ByteBuffer;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-04
 * Time:   14:54
 * Life with Passion, Code with Creativity.
 */
public class TestCase {
    public static final String TAG = "TestCase";

    public static void test() {
        //start
        Log.i(TAG, "device " + Build.BRAND + " " + Build.BOARD);
        Log.i(TAG, "action, count, total(ns), avg(ns)");
        testJavaAdd();
        testCppAdd();
        testJavaBatchAdd();
        testCppBatchAdd();
        testPassByteArrayToNative();
        testPassByteBufferToNative();
        testJavaBatchMemset();
        testJavaReadDirectBuffer();
        testCppBatchMemcpy();
        testJavaBatchArrayCopy();

        Log.i(TAG, "=================================\n\n\n");
    }
    /*
    | java add(0xffff+ 1) | 1M |
| cpp add(0xffff+ 1) | 1M |
| java batch(1M) add(0xffff+ 1) | 1M |
| cpp batch(1M) add(0xffff+ 1) | 1M |
| passByteArrayToNative (1M) | 1K |
| passByteBufferToNative (1M) | 1K |
| java iterator array (1M) | 1K |
| java read directBuffer (1M) | 1k |
| cppMemoryCpy (1M) | 1K |
| System.arrayCopy 1M | 1K |
     */

    private static final int BIG_COUNT = 1024 * 1024;
    private static final int SMALL_COUNT = 1024;

    public static void testJavaAdd() {
        long time = System.nanoTime();
        for (int i = 0; i < BIG_COUNT; i++) {
            JavaJniPerformanceCompare.javaAdd(0xffff, 1);
        }
        time = System.nanoTime() - time;

        Log.i(TAG, "java add(0xffff+ 1) , 1M ," + time + ", " + time / BIG_COUNT);
    }

    public static void testCppAdd() {
        long time = System.nanoTime();
        for (int i = 0; i < BIG_COUNT; i++) {
            JavaJniPerformanceCompare.add(0xffff, 1);
        }
        time = System.nanoTime() - time;

        Log.i(TAG, "cpp add(0xffff+ 1) , 1M ," + time + ", " + time / BIG_COUNT);
    }

    public static void testJavaBatchAdd() {
        long time = System.nanoTime();
        for (int i = 0; i < SMALL_COUNT; i++) {
            JavaJniPerformanceCompare.javaBatchAdd(0xffff, 1, SMALL_COUNT);
        }
        time = System.nanoTime() - time;

        Log.i(TAG, "javaBatchAdd(0xffff+ 1) 1K, 1K ," + time + ", " + time / BIG_COUNT);
    }

    public static void testCppBatchAdd() {
        long time = System.nanoTime();
        for (int i = 0; i < SMALL_COUNT; i++) {
            JavaJniPerformanceCompare.batchAdd(0xffff, 1, SMALL_COUNT);
        }
        time = System.nanoTime() - time;

        Log.i(TAG, "cppBatchAdd(0xffff+ 1) 1K, 1K ," + time + ", " + time / BIG_COUNT);
    }

    public static void testJavaBatchMemset() {
        long totalTime = System.nanoTime();
        JavaJniPerformanceCompare.javaBatchMemset(BIG_COUNT, SMALL_COUNT);
        totalTime = System.nanoTime() - totalTime;

        Log.i(TAG, "javaBatchMemset(1M) , 1K ," + totalTime + ", " + totalTime / SMALL_COUNT);
    }

    public static void testCppBatchMemset() {
        long totalTime = System.nanoTime();
        JavaJniPerformanceCompare.cppBatchMemset(BIG_COUNT, SMALL_COUNT);
        totalTime = System.nanoTime() - totalTime;

        Log.i(TAG, "cppBatchMemset(1M) , 1K ," + totalTime + ", " + totalTime / SMALL_COUNT);
    }

    public static void testPassByteArrayToNative() {
        byte[] data = new byte[BIG_COUNT];

        long totalTime = 0;
        long startTime;
        for (int i = 0; i < SMALL_COUNT; i++) {

            setValue(data, (byte) 0);

            startTime = System.nanoTime();
            JavaJniPerformanceCompare.passByteArrayToNative(data);
            totalTime += System.nanoTime() - startTime;

            assertValue(data, (byte) 1);
        }

        Log.i(TAG, "passByteArrayToNative(1M) , 1K ," + totalTime + ", " + totalTime / SMALL_COUNT);
    }

    public static void testPassByteBufferToNative() {
        ByteBuffer data = ByteBuffer.allocateDirect(BIG_COUNT);

        long totalTime = 0;
        long startTime;
        for (int i = 0; i < SMALL_COUNT; i++) {

            startTime = System.nanoTime();
            //set data number
            data.limit(BIG_COUNT);
            JavaJniPerformanceCompare.passByteBufferToNative(data);
            totalTime += System.nanoTime() - startTime;

            assertValue(data, (byte) 1);

            data.clear();
        }

        Log.i(TAG, "passByteBufferToNative(1M) , 1K ," + totalTime + ", " + totalTime / SMALL_COUNT);
    }

    public static void testJavaReadDirectBuffer() {
        byte[] javaData = new byte[BIG_COUNT];
        ByteBuffer buffer = ByteBuffer.allocateDirect(BIG_COUNT);

        long totalTime = 0;
        long startTime;
        for (int i = 0; i < SMALL_COUNT; i++) {

            setValue(javaData, (byte) 0);
            JavaJniPerformanceCompare.passByteBufferToNative(buffer);

            startTime = System.nanoTime();
            //do the work
            buffer.get(javaData, 0, BIG_COUNT);
            totalTime += System.nanoTime() - startTime;

            buffer.clear();
            assertValue(javaData, (byte) 1);
        }

        Log.i(TAG, "javaReadDirectBuffer(1M) , 1K ," + totalTime + ", " + totalTime / SMALL_COUNT);
    }

    public static void testCppBatchMemcpy() {
        long time = System.nanoTime();
        JavaJniPerformanceCompare.javaBatchMemcpy(BIG_COUNT, SMALL_COUNT);
        time = System.nanoTime() - time;

        Log.i(TAG, "javaBatchMemcpy(1M) , 1K ," + time + ", " + time / BIG_COUNT);
    }

    public static void testJavaBatchArrayCopy() {
        long time = System.nanoTime();
        JavaJniPerformanceCompare.cppBatchMemcpy(BIG_COUNT, SMALL_COUNT);
        time = System.nanoTime() - time;

        Log.i(TAG, "cppBatchMemcpy(1M) , 1K ," + time + ", " + time / BIG_COUNT);
    }

    public static void setValue(@NonNull byte[] arr, byte value) {
        for (int i = 0; i < arr.length; i++) {
            arr[i] = value;
        }
    }

    public static void assertValue(@NonNull byte[] arr, byte value) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] != value) {
                throw new AssertionError("array item arr[" + i + "]=" + arr[i] + " is not " + value);
            }
        }
    }

    private static byte[] cache = new byte[BIG_COUNT];
    public static void assertValue(@NonNull ByteBuffer data, byte value) {
        data.get(cache, 0, BIG_COUNT);
        assertValue(cache, value);
    }
}
