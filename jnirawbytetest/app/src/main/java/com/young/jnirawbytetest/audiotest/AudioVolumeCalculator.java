package com.young.jnirawbytetest.audiotest;

import android.os.Environment;
import android.support.annotation.NonNull;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

/**
 * <pre>
 * Author: taylorcyang@tencent.com
 * Date:   2016-11-30
 * Time:   19:23
 * Life with Passion, Code with Creativity.
 * </pre>
 */
public class AudioVolumeCalculator {

    public static double calculateAudioVolume(byte[] data, int length) {
        length /= 2;

        double sumOfPower = 0;

        double db = 0;

        for (int i = 0; i < length; i += 2) {
            short pcm16 = (short) (((data[i + 1] & 0xff) << 8) | (data[i] & 0xff));
            sumOfPower += (double) pcm16 * pcm16;
        }
        sumOfPower = sumOfPower / length;

        if (sumOfPower > 0) {
            db = 10 * Math.log10(sumOfPower);
        }

        return db;
    }

    @NonNull
    private final FileInputStream mFileInputStream;
    private final byte[] mChunk;

    public AudioVolumeCalculator() {
        try {
            mFileInputStream = new FileInputStream(
                    new File(
                            Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS),
                            "pp.stereo.pcm.raw"
                    ));
        } catch (IOException e) {
            throw new IllegalStateException(e);
        }

        mChunk = new byte[2048];
    }

    public int nextVolumeGain() {
        try {
            int count = mFileInputStream.read(mChunk);

        } catch (IOException e) {

        }
        return (int) calculateAudioVolume(mChunk, mChunk.length);
    }
}
