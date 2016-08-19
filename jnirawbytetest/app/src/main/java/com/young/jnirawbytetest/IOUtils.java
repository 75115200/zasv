package com.young.jnirawbytetest;

import android.support.annotation.Nullable;

import java.io.Closeable;
import java.io.IOException;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-19
 * Time:   17:09
 * Life with Passion, Code with Creativity.
 */
public class IOUtils {
    public static void close(@Nullable Closeable c) {
        if (c != null) {
            try {
                c.close();
            } catch (IOException e) {
            }
        }
    }

}
