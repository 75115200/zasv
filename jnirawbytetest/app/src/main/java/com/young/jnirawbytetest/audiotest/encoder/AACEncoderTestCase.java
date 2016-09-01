package com.young.jnirawbytetest.audiotest.encoder;

import android.media.AudioFormat;
import android.os.Environment;
import android.os.SystemClock;
import android.util.Log;

import com.young.jnirawbytetest.audiotest.logic.PCMFormat;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-09-01
 * Time:   17:33
 * Life with Passion, Code with Creativity.
 */
public class AACEncoderTestCase {
    private static final String TAG = "AACEncoderTestCase";

    public static final String DOWNLOAD_PATH = Environment.getExternalStoragePublicDirectory(
            Environment.DIRECTORY_DOWNLOADS).getAbsolutePath();

    private static final String MONO_PCM = DOWNLOAD_PATH + "/pp.mono.pcm.raw";
    private static final String STEREO_PCM = DOWNLOAD_PATH + "/pp.stereo.pcm.raw";

    private static final String OUT_PUT_M4A_PATH = DOWNLOAD_PATH + "/pp.encode.m4a";

    public static void testEncodeAndMuxerToM4A() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                encodeAndMuxer();
            }
        }, TAG).start();

    }

    private static void encodeAndMuxer() {
        try {
            Log.i(TAG, "encodeAndMuxer: start");
            PCMFormat format = new PCMFormat();
            format.sampleRate = 44100;
            format.outChannelConfig = AudioFormat.CHANNEL_OUT_STEREO;
            format.bitRate = 96 * 1000;
            format.bufferSize = 0b0100_0000__0000_0000;

            AACMuxer aacMuxer = new DroidM4AMuxer(OUT_PUT_M4A_PATH);
            AACAudioEncoder encoder = new AACAudioEncoder(format, aacMuxer);
            InputStream in = new BufferedInputStream(new FileInputStream(STEREO_PCM));

            long startTime = SystemClock.uptimeMillis();

            byte[] buffer = new byte[format.bufferSize];
            int totalBytes = 0;
            int read;
            long timeUs = 1;
            while ((read = in.read(buffer)) > 0) {
                totalBytes += read;
                timeUs = totalBytes * 1000L * 1000 / (44100 * 2 * 2);
                Log.i(TAG, "encodeAndMuxer: timeUs=" + timeUs);
                encoder.writeData(buffer, read, timeUs, in.available() == 0);
            }

            encoder.release();

            long timeCost = (SystemClock.uptimeMillis() - startTime);

            Log.i(TAG, "encodeAndMuxer: done"
                    + " timeCost=" + timeCost
                    + " speed=" + (timeUs / 1000 / (float) timeCost) + "x"
            );
        } catch (IOException | IllegalStateException | IllegalArgumentException e) {
            Log.e(TAG, "encodeAndMuxer: ", e);
        }
    }
}
