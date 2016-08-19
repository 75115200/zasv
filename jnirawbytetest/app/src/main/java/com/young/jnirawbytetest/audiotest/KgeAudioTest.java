package com.young.jnirawbytetest.audiotest;

import android.media.AudioFormat;
import android.os.Bundle;

import com.young.jenny.annotation.NativeClass;
import com.young.jnirawbytetest.IOUtils;
import com.young.jnirawbytetest.audiotest.logic.PCMAudioPlayer;
import com.young.jnirawbytetest.audiotest.logic.PCMFormat;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.InputStream;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-19
 * Time:   11:18
 * Life with Passion, Code with Creativity.
 */
@NativeClass
public class KgeAudioTest {
    static {
        System.loadLibrary("audio-test");
    }

    public static void testClean2() throws  Exception {
        PCMFormat format = new PCMFormat();
        format.sampleRate = 44100;
        format.audioFormat = AudioFormat.ENCODING_PCM_16BIT;
        format.outChannelConfig = AudioFormat.CHANNEL_OUT_MONO;
        format.bufferSize = PCMAudioPlayer.getMinBuffeSize(format);
        final int bufferSize = format.bufferSize << 2;
        PCMAudioPlayer player = new PCMAudioPlayer(format);
        Bundle param = new Bundle();

        byte[] buffer = new byte[bufferSize];

        InputStream in = new BufferedInputStream(new FileInputStream("/sdcard/mono.pcm"));
        KalaClean2 clean2 = new KalaClean2(44100, 1);

        int readLen;
        while ((readLen = in.read(buffer, 0, bufferSize)) > 0) {
            clean2.process(buffer, readLen);
            player.write(buffer, 0, readLen, param);
        }

        player.release();
        clean2.release();
        IOUtils.close(in);
    }

    public static void mixTest() throws Exception {
        PCMFormat format = new PCMFormat();
        format.sampleRate = 44100;
        format.audioFormat = AudioFormat.ENCODING_PCM_16BIT;
        format.outChannelConfig = AudioFormat.CHANNEL_OUT_STEREO;
        format.bufferSize = PCMAudioPlayer.getMinBuffeSize(format);
        final int bufferSize = format.bufferSize << 2;
        PCMAudioPlayer player = new PCMAudioPlayer(format);
        Bundle param = new Bundle();

        final byte[] bgmBuffer = new byte[bufferSize];
        final byte[] vocalBuffer = new byte[bufferSize];
        final byte[] outBuffer = new byte[bufferSize];

        InputStream bgmIn = new BufferedInputStream(new FileInputStream("/sdcard/bgm.stereo.pcm"));
        InputStream vocalIn = new BufferedInputStream(new FileInputStream("/sdcard/haha.stereo.pcm"));

        final KalaMix mix = new KalaMix(format.sampleRate, 2);

        int bgmRead;
        int vocalRead;
        while ((bgmRead = bgmIn.read(bgmBuffer, 0, bufferSize)) > 0
                && (vocalRead = vocalIn.read(vocalBuffer, 0, bufferSize)) > 0) {
            mix.process(bgmBuffer, bufferSize,
                        vocalBuffer, bufferSize,
                        outBuffer, bufferSize);

            player.write(outBuffer, 0, bufferSize, param);
        }

        player.release();
        mix.release();
        IOUtils.close(bgmIn);
        IOUtils.close(vocalRead);
    }
}
