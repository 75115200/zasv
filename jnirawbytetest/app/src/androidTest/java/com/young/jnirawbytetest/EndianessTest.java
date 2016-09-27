package com.young.jnirawbytetest;

import android.support.test.runner.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

/**
 * Author: landerlyoung@gmail.com
 * Date:   2016-08-10
 * Time:   10:56
 * Life with Passion, Code with Creativity.
 */
@RunWith(AndroidJUnit4.class)
public class EndianessTest {

    @Test
    public void testEndianess() {
        byte[] b = new byte[1024];
        JavaJniPerformanceCompare.passByteArrayToNative(b);

        short[] s = new short[1024 * 1024];
        s[0] = 0x0102;
        JavaJniPerformanceCompare.testEndianess(s);

    }
}
