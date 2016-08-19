package com.young.jnirawbytetest.audiotest.logic;

import android.media.AudioManager;
import android.media.AudioTrack;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.NonNull;

import java.nio.ByteBuffer;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-09
 * Time:   19:47
 * Life with Passion, Code with Creativity.
 */
public class PCMAudioPlayer implements AudioConsumer {
    private static final String TAG = "PCMAudioPlayer";

    private AudioTrack mAudioTrack;
    private byte[] mByteBuffer;

    public static int getMinBuffeSize(@NonNull PCMFormat format) {
        return AudioTrack.getMinBufferSize(format.sampleRate, format.outChannelConfig, format.audioFormat);
    }

    public PCMAudioPlayer(@NonNull PCMFormat format)
            throws IllegalStateException, IllegalArgumentException {
        mAudioTrack = new AudioTrack(
                AudioManager.STREAM_MUSIC,
                format.sampleRate,
                format.outChannelConfig,
                format.audioFormat,
                format.bufferSize,
                AudioTrack.MODE_STREAM);
        mAudioTrack.play();
    }

    @Override
    public void write(@NonNull byte[] data, int offset, int len, @NonNull Bundle param) {
        mAudioTrack.write(data, offset, len);
    }

    /**
     * write data from <code>data</code>to audio track,
     * bytes ranged from 0 to data.limit() bytes
     *
     * @param data
     * @param param
     */
    @Override
    public void write(@NonNull ByteBuffer data, @NonNull Bundle param) {
        final int len = data.remaining();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            mAudioTrack.write(data, len, AudioTrack.WRITE_BLOCKING);
        } else {
            //get byte[] data from the ByteBuffer
            byte[] buffer = getByteBuffer(len);
            data.get(buffer, 0, len);
            write(buffer, 0, len, param);
        }
    }

    @NonNull
    private byte[] getByteBuffer(int size) {
        if (mByteBuffer == null || mByteBuffer.length < size) {
            mByteBuffer = new byte[size];
        }
        return mByteBuffer;
    }

    @Override
    public void release() {
        if (mAudioTrack != null) {
            mAudioTrack.release();
            mAudioTrack = null;
        }
        mByteBuffer = null;
    }
}
