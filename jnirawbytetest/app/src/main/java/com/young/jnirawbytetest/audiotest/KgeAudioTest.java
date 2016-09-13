package com.young.jnirawbytetest.audiotest;

import android.media.AudioFormat;
import android.os.Bundle;
import android.os.SystemClock;
import android.util.Log;

import com.tencent.audioeffect.effect.KalaReverb;
import com.tencent.audioeffect.effect.KalaVolumeScaler;
import com.young.jnirawbytetest.IOUtils;
import com.young.jnirawbytetest.audiotest.logic.PCMAudioPlayer;
import com.young.jnirawbytetest.audiotest.logic.PCMFormat;
import com.young.jnirawbytetest.supersound.SuperSoundWrapper;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.InputStream;

import io.github.landerlyoung.jenny.NativeClass;

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
        System.loadLibrary("audio_test");
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
        stereo = true;
        PCMFormat format = new PCMFormat();
        format.sampleRate = 44100;
        format.audioFormat = AudioFormat.ENCODING_PCM_16BIT;
        if (stereo) {
            format.outChannelConfig = AudioFormat.CHANNEL_OUT_STEREO;
        } else {
            format.outChannelConfig = AudioFormat.CHANNEL_OUT_MONO;
        }
        format.bufferSize = PCMAudioPlayer.getMinBuffeSize(format);
        PCMAudioPlayer player = new PCMAudioPlayer(format);
        Bundle param = new Bundle();

        final int monoBufferSize = format.bufferSize << 1;
        final int stereoBufferSize = monoBufferSize << 1;

        final byte[] bgmBuffer = new byte[stereoBufferSize];
        final byte[] vocalBuffer = new byte[monoBufferSize];
        final byte[] outBuffer = new byte[stereoBufferSize];

        InputStream bgmIn = new BufferedInputStream(new FileInputStream(
                stereo ? PCM.STEREO_MUSIC : PCM.MONO_MUSIC));

        stereo = false;
        InputStream vocalIn = new BufferedInputStream(new FileInputStream(
                stereo ? PCM.STEREO : PCM.MONO));

        final KalaMix mix = new KalaMix(
                format.sampleRate, 2,1
//                stereo ? 2 : 1,
//                stereo ? 2 : 1
        );

        int bgmRead;
        int vocalRead;
        while (!Thread.interrupted() &&
                (bgmRead = bgmIn.read(bgmBuffer, 0, stereoBufferSize)) > 0
                && (vocalRead = vocalIn.read(vocalBuffer, 0, monoBufferSize)) > 0) {
            mix.process(bgmBuffer, stereoBufferSize,
                        vocalBuffer, monoBufferSize,
                        outBuffer, stereoBufferSize);

            player.write(outBuffer, 0, stereoBufferSize, param);
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

    public static void reverbTest(int typeId) throws Exception {
        KalaReverb kalaReverb = new KalaReverb(44100, 1);
        int idDefault = kalaReverb.getIdDefault();

        int[] out = new int[2];
        kalaReverb.getIdRange(out);
        int maxId = out[0];
        int minId = out[1];

        Log.i(TAG, "reverb: idDefault=" + idDefault);
        Log.i(TAG, "reverb: idRange=[" + minId + ", " + maxId + "]");

        final int bufferSize = 1024 * 8;
        byte[] buffer = new byte[bufferSize];
        final int outBufferSize = bufferSize;
        byte[] outbuf = new byte[outBufferSize];

        PCMFormat format = new PCMFormat();
        format.sampleRate = 44100;
        format.audioFormat = AudioFormat.ENCODING_PCM_16BIT;
        format.outChannelConfig = AudioFormat.CHANNEL_OUT_MONO;
        format.bufferSize = bufferSize;//PCMAudioPlayer.getMinBuffeSize(format);
        PCMAudioPlayer p = new PCMAudioPlayer(format);
        Bundle outParam = new Bundle();

        InputStream in = new BufferedInputStream(new FileInputStream(PCM.MONO_MUSIC));

        kalaReverb.setTypeId(typeId);

        long start = SystemClock.elapsedRealtime();
        while (!Thread.interrupted() && in.read(buffer, 0, bufferSize) > 0) {
            //kalaReverb.setTypeId(typeId);
            final int outLen = kalaReverb.process(buffer, bufferSize, outbuf, outBufferSize);
            p.write(buffer, 0, outLen, outParam);
            Log.i(TAG, "reverb: inLen=" + bufferSize + " outLen=" + outLen);
        }

        Log.i(TAG, "reverb: runTime " + (SystemClock.elapsedRealtime() - start));

        kalaReverb.release();
        IOUtils.close(in);
    }

    public static void volumeScaleTest(int scale) throws Exception {
        PCMFormat format = new PCMFormat();
        format.sampleRate = 44100;
        format.audioFormat = AudioFormat.ENCODING_PCM_16BIT;
        format.outChannelConfig = AudioFormat.CHANNEL_OUT_MONO;
        format.bufferSize = PCMAudioPlayer.getMinBuffeSize(format);
        final int bufferSize = format.bufferSize << 2;
        PCMAudioPlayer player = new PCMAudioPlayer(format);
        Bundle param = new Bundle();

        byte[] buffer = new byte[bufferSize];

        InputStream in = new BufferedInputStream(new FileInputStream(PCM.MONO_MUSIC));
        KalaVolumeScaler scaler = new KalaVolumeScaler(44100, 1);

        scaler.setScaleFactor(scale);

        int readLen;
        while (!Thread.interrupted() &&
                (readLen = in.read(buffer, 0, bufferSize)) > 0) {
            int size = scaler.process(buffer, readLen);
            player.write(buffer, 0, size, param);
        }

        player.release();
        scaler.release();
        IOUtils.close(in);
    }

    public static void superSound(int type) throws Exception {
        final int channelCount = 2;

        PCMFormat format = new PCMFormat();
        format.sampleRate = 44100;
        format.audioFormat = AudioFormat.ENCODING_PCM_16BIT;
        format.outChannelConfig = channelCount == 1 ? AudioFormat.CHANNEL_OUT_MONO : AudioFormat.CHANNEL_OUT_STEREO;
        format.bufferSize = PCMAudioPlayer.getMinBuffeSize(format);
        PCMAudioPlayer player = new PCMAudioPlayer(format);
        Bundle param = new Bundle();

        final int sampleSize = channelCount * 2;
        final int pcmSize = 2;
        final int bufferSize = format.bufferSize << sampleSize;

        byte[] buffer = new byte[bufferSize];

        InputStream in = new BufferedInputStream(new FileInputStream(
                channelCount == 1
                        ? PCM.MONO_MUSIC
                        : PCM.STEREO_MUSIC
        ));
        SuperSoundWrapper s = new SuperSoundWrapper(44100, channelCount);

        SuperSoundWrapper.SUPERSOUND_EFFECT_TYPE t =
                SuperSoundWrapper.SUPERSOUND_EFFECT_TYPE.values()[type];
        float intensity = 1f;
        switch (t) {
            case SUPERSOUND_BASS_TYPE: {
                intensity = SuperSoundWrapper.SUPERSOUND_BASS_PARAM_DEFAUT;
                break;
            }
            case SUPERSOUND_STUDIO_TYPE: {
                intensity = SuperSoundWrapper.SUPERSOUND_STUDIO_PARAM_DEFAUT;
                break;
            }
            case SUPERSOUND_SURROUND_TYPE: {
                intensity = SuperSoundWrapper.SUPERSOUND_SURROUND_PARAM_DEFAUT;
                break;
            }
            case SUPERSOUND_VOCAL_TYPE: {
                intensity = SuperSoundWrapper.SUPERSOUND_VOCAL_PARAM_DEFAUT;
                break;
            }
        }

        s.setIntensity(t, intensity);

        int lookAhead = s.getLookAhead();
        Log.v(TAG, "superSound: lookAhead=" + lookAhead);

        int readLen;
        while (!Thread.interrupted() &&
                (readLen = in.read(buffer, 0, bufferSize)) > 0) {
            s.process(buffer, readLen / (pcmSize));
            int size = readLen - lookAhead * pcmSize;

            player.write(buffer, 0, size, param);
        }

        player.release();
        s.release();
        IOUtils.close(in);
    }

}
