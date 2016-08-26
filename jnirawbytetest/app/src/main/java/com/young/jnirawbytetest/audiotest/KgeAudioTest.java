package com.young.jnirawbytetest.audiotest;

import android.media.AudioFormat;
import android.os.Bundle;
import android.os.SystemClock;
import android.util.Log;

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
    private static final String TAG = "KgeAudioTest";
    static {
        loadLib();
    }

    public static void loadLib() {
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

        InputStream in = new BufferedInputStream(new FileInputStream(PCM.MONO));
        KalaClean2 clean2 = new KalaClean2(44100, 1);

        int readLen;
        while (!Thread.interrupted() &&
                (readLen = in.read(buffer, 0, bufferSize)) > 0) {
            clean2.process(buffer, readLen);
            player.write(buffer, 0, readLen, param);
        }

        player.release();
        clean2.release();
        IOUtils.close(in);
    }

    public static void mixTest(boolean stereo) throws Exception {
        PCMFormat format = new PCMFormat();
        format.sampleRate = 44100;
        format.audioFormat = AudioFormat.ENCODING_PCM_16BIT;
        if (stereo) {
            format.outChannelConfig = AudioFormat.CHANNEL_OUT_STEREO;
        } else {
            format.outChannelConfig = AudioFormat.CHANNEL_OUT_MONO;
        }
        format.bufferSize = PCMAudioPlayer.getMinBuffeSize(format);
        final int bufferSize = format.bufferSize << 2;
        PCMAudioPlayer player = new PCMAudioPlayer(format);
        Bundle param = new Bundle();

        final byte[] bgmBuffer = new byte[bufferSize];
        final byte[] vocalBuffer = new byte[bufferSize];
        final byte[] outBuffer = new byte[bufferSize];

        InputStream bgmIn = new BufferedInputStream(new FileInputStream(
                stereo ? PCM.STEREO_MUSIC : PCM.MONO_MUSIC));
        InputStream vocalIn = new BufferedInputStream(new FileInputStream(
                stereo ? PCM.STEREO : PCM.MONO));

        final KalaMix mix = new KalaMix(format.sampleRate, 2);

        int bgmRead;
        int vocalRead;
        while (!Thread.interrupted() &&
                (bgmRead = bgmIn.read(bgmBuffer, 0, bufferSize)) > 0
                && (vocalRead = vocalIn.read(vocalBuffer, 0, bufferSize)) > 0) {
            mix.process(bgmBuffer, bufferSize,
                        vocalBuffer, bufferSize,
                        outBuffer, bufferSize);

            player.write(outBuffer, 0, bufferSize, param);
        }

        player.release();
        mix.release();
        IOUtils.close(bgmIn);
        IOUtils.close(vocalIn);
    }

    public static void voiceShiftTest(int typeId) throws Exception {
        KalaVoiceShift voiceShift = new KalaVoiceShift(44100, 2);
        int idDefault = voiceShift.getIdDefault();

        int[] out = new int[2];
        voiceShift.getIdRange(out);
        int maxId = out[0];
        int minId = out[1];

        Log.i(TAG, "voiceShiftTest: idDefault=" + idDefault);
        Log.i(TAG, "voiceShiftTest: idRange=[" + minId + ", " + maxId + "]");

        Log.i(TAG, "voiceShiftTest:"
                + "\nBABY name:\t" + voiceShift.getNameById(KalaVoiceShift.KALA_VOICE_SHIFT_BABY)
                + "\nAUTOTUNE name:\t" + voiceShift.getNameById(KalaVoiceShift.KALA_VOICE_SHIFT_AUTOTUNE)
                + "\nBASSO name:\t" + voiceShift.getNameById(KalaVoiceShift.KALA_VOICE_SHIFT_BASSO)
                + "\nSOPRANO name:\t" + voiceShift.getNameById(KalaVoiceShift.KALA_VOICE_SHIFT_SOPRANO)
                + "\nCHORUS name:\t" + voiceShift.getNameById(KalaVoiceShift.KALA_VOICE_SHIFT_CHORUS)
                + "\nMETAL name:\t" + voiceShift.getNameById(KalaVoiceShift.KALA_VOICE_SHIFT_METAL)
        );

        final int bufferSize = 1024 * 8;
        byte[] buffer = new byte[bufferSize];
        final int outBufferSize = bufferSize * 4;
        byte[] outbuf = new byte[outBufferSize];

        PCMFormat format = new PCMFormat();
        format.sampleRate = 44100;
        format.audioFormat = AudioFormat.ENCODING_PCM_16BIT;
        format.outChannelConfig = AudioFormat.CHANNEL_OUT_STEREO;
        format.bufferSize = PCMAudioPlayer.getMinBuffeSize(format);
        PCMAudioPlayer p = new PCMAudioPlayer(format);
        Bundle outParam = new Bundle();

        InputStream in = new BufferedInputStream(new FileInputStream(PCM.STEREO));

        voiceShift.setTypeId(typeId);

        long start = SystemClock.elapsedRealtime();
        while (!Thread.interrupted() && in.read(buffer, 0, bufferSize) > 0) {
            final int outLen = voiceShift.process(buffer, bufferSize, outbuf, outBufferSize);
            p.write(buffer, 0, outLen, outParam);
            Log.i(TAG, "voiceShiftTest: inLen=" + bufferSize + " outLen=" + outLen);
        }

        Log.i(TAG, "voiceShiftTest: runTime " + (SystemClock.elapsedRealtime() - start));

        voiceShift.release();
        IOUtils.close(in);
    }

    public static void testTone(int toneVal) throws Exception {
        PCMFormat format = new PCMFormat();
        format.sampleRate = 44100;
        format.audioFormat = AudioFormat.ENCODING_PCM_16BIT;
        format.outChannelConfig = AudioFormat.CHANNEL_OUT_STEREO;
        format.bufferSize = PCMAudioPlayer.getMinBuffeSize(format);
        final int bufferSize = format.bufferSize << 2;
        PCMAudioPlayer player = new PCMAudioPlayer(format);
        Bundle param = new Bundle();

        byte[] buffer = new byte[bufferSize];
        byte[] outBuffer = new byte[bufferSize];

        InputStream in = new BufferedInputStream(new FileInputStream(PCM.STEREO));
        KalaToneShift tone = new KalaToneShift(44100, 1);

        tone.setShiftValue(toneVal);

        int readLen;
        while (!Thread.interrupted() &&
                (readLen = in.read(buffer, 0, bufferSize)) > 0) {
            int size = tone.process(buffer, bufferSize, outBuffer, bufferSize);
            player.write(outBuffer, 0, size, param);
        }

        player.release();
        tone.release();
        IOUtils.close(in);
    }

    public static void testGain() throws Exception {
        PCMFormat format = new PCMFormat();
        format.sampleRate = 44100;
        format.audioFormat = AudioFormat.ENCODING_PCM_16BIT;
        format.outChannelConfig = AudioFormat.CHANNEL_OUT_STEREO;
        format.bufferSize = PCMAudioPlayer.getMinBuffeSize(format);
        final int bufferSize = format.bufferSize << 2;
        PCMAudioPlayer player = new PCMAudioPlayer(format);
        Bundle param = new Bundle();

        byte[] buffer = new byte[bufferSize];

        InputStream in = new BufferedInputStream(new FileInputStream(PCM.STEREO));
        KalaAudioGain gain = new KalaAudioGain(44100, 2);

        int readLen;
        while (!Thread.interrupted() &&
                (readLen = in.read(buffer, 0, bufferSize)) > 0) {
            int size = gain.process(buffer, readLen);
            player.write(buffer, 0, size, param);
        }

        player.release();
        gain.release();
        IOUtils.close(in);
    }
}
