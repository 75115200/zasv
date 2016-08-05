package com.young.jnirawbytetest;

import android.os.Build;
import android.support.test.runner.AndroidJUnit4;
import android.util.Log;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.FixMethodOrder;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.MethodSorters;

/**
 * Instrumentation test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
@FixMethodOrder(MethodSorters.JVM)
public class ExampleInstrumentedTest {

    @BeforeClass
    public static void start() {
        //start
        Log.i(TestCase.TAG, "device " + Build.MODEL + " " + Build.BOARD + " API-" +Build.VERSION.SDK_INT);
        Log.i(TestCase.TAG, "action, count, total(ns), avg(ns)");
    }

    @Test
    public void testJavaAdd() {
        TestCase.testJavaAdd();
    }

    @Test
    public void testCppAdd() {
        TestCase.testCppAdd();
    }

    @Test
    public void testJavaBatchAdd() {
        TestCase.testJavaBatchAdd();
    }

    @Test
    public void testCppBatchAdd() {
        TestCase.testCppBatchAdd();
    }

    @Test
    public void testPassByteArrayToNative() {
        TestCase.testPassByteArrayToNative();
    }

    @Test
    public void testPassByteBufferToNative() {
        TestCase.testPassByteBufferToNative();
    }

    @Test
    public void testJavaBatchMemset() {
        TestCase.testJavaBatchMemset();
    }

    @Test
    public void testCppBatchMemset() {
        TestCase.testCppBatchMemset();
    }

    @Test
    public void testJavaReadDirectBuffer() {
        TestCase.testJavaReadDirectBuffer();
    }

    @Test
    public void testCppBatchMemcpy() {
        TestCase.testCppBatchMemcpy();
    }

    @Test
    public void testJavaBatchArrayCopy() {
        TestCase.testJavaBatchArrayCopy();
    }

    @AfterClass
    public static void end() {
        Log.i(TestCase.TAG, "=================================\n\n\n");
    }
}
