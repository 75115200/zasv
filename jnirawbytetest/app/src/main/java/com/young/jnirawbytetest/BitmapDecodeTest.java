package com.young.jnirawbytetest;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Process;
import android.support.annotation.NonNull;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;

/**
 * <pre>
 * Author: taylorcyang@tencent.com
 * Date:   2017-02-13
 * Time:   14:44
 * Life with Passion, Code with Creativity.
 * </pre>
 */
public class BitmapDecodeTest {
    private static final String TAG = "BitmapDecodeTest";

    public static void test(@NonNull final Context context) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                //highest
                Process.setThreadPriority(Process.THREAD_PRIORITY_URGENT_AUDIO);
                runTest(context);
            }
        }).start();
    }

    private static void runTest(@NonNull Context context) {
        try {
            final int retryCount = 100;
            // 1280 x 720
            InputStream in = context.getAssets().open("bg_splashscreen_enter.jpg");
            BitmapFactory.Options opt = new BitmapFactory.Options();
            opt.inDensity = 320;

            opt.inTargetDensity = 480;
            long xxhdpi = decode(in, opt, retryCount);
            Log.i(TAG, "test: xxhdpi=" + xxhdpi);


            opt.inTargetDensity = 320;
            long xhdpi = decode(in, opt, retryCount);
            Log.i(TAG, "test: xhdpi=" + xhdpi);

            opt.inTargetDensity = 240;
            long hdpi = decode(in, opt, retryCount);
            Log.i(TAG, "test: hdpi=" + hdpi);

            opt.inTargetDensity = 160;
            long mdpi = decode(in, opt, retryCount);
            Log.i(TAG, "test: mdpi=" + mdpi);

            Log.i(TAG, "test: [xxhdpi, xhdpi, hdpi, mdpi] "
                    + "\n abs = [" + xxhdpi + ", " + xhdpi + ", " + hdpi + ", " + mdpi + "]"
                    + "\n per = [" + xxhdpi / (float) xhdpi + ", " + 1.0f + ", " + hdpi / (float) xhdpi + ", " + mdpi / (float) xhdpi + "]");

            in.close();
        } catch (IOException e) {
            Log.e(TAG, "test: ", e);

        }
    }

    private static long decode(InputStream in, BitmapFactory.Options options, int count) throws IOException {
        long totalNanos = 0;
        for (int i = 0; i < count; i++) {
            in.reset();
            long start = System.nanoTime();
            Bitmap tmp = BitmapFactory.decodeStream(in, null, options);
            totalNanos += System.nanoTime() - start;
            tmp.recycle();
        }
        return totalNanos;
    }
}
