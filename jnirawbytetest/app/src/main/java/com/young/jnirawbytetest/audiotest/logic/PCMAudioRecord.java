package com.young.jnirawbytetest.audiotest.logic;

import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.util.Log;


import java.nio.ByteBuffer;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-10
 * Time:   16:35
 * Life with Passion, Code with Creativity.
 */
public class PCMAudioRecord implements AudioProducer {
    private static final String TAG = "PCMAudioRecord";

    public static int getMinBufferSize(@NonNull PCMFormat format) {
        return AudioRecord.getMinBufferSize(format.sampleRate, format.inChannelConfig, format.audioFormat);
    }

    private AudioRecord mAudioRecord;

    public boolean init(@NonNull PCMFormat pcmFormat) {
        try {
            mAudioRecord = new AudioRecord(
                    MediaRecorder.AudioSource.MIC,
                    pcmFormat.sampleRate,
                    pcmFormat.inChannelConfig,
                    pcmFormat.audioFormat,
                    pcmFormat.bufferSize);
            mAudioRecord.startRecording();
        } catch (IllegalArgumentException e) {
            Log.e(TAG, "init: ", e);
            return false;
        }
        return true;
    }

    @Override
    public void read(@NonNull byte[] data, int offset, int len, @NonNull Bundle param) {
        mAudioRecord.read(data, offset, len);
    }

    @Override
    public void read(@NonNull ByteBuffer data, @NonNull Bundle param) {
        int read = mAudioRecord.read(data, data.capacity());
        if (read == AudioRecord.ERROR_BAD_VALUE) {
            //notify read failed
            //param.putString()
        } else if (read == AudioRecord.ERROR_INVALID_OPERATION) {
            //notify read failed
            //param.putString()
        } else {
            data.position(read);
        }
    }

    @Override
    public void release() {
        mAudioRecord.release();
    }
}
