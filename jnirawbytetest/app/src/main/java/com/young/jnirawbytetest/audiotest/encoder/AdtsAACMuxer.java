package com.young.jnirawbytetest.audiotest.encoder;

import android.media.MediaCodec;
import android.media.MediaFormat;
import android.support.annotation.NonNull;

import com.young.jnirawbytetest.IOUtils;

import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-09-01
 * Time:   20:39
 * Life with Passion, Code with Creativity.
 */
public class AdtsAACMuxer implements AACMuxer {

    private final OutputStream mOutputStream;




    public AdtsAACMuxer(@NonNull String filePath) throws IOException {
        this(new BufferedOutputStream(new FileOutputStream(filePath)));
    }

    public AdtsAACMuxer(@NonNull OutputStream outputStream) {
        mOutputStream = outputStream;
    }

    @Override
    public int addTrack(@NonNull MediaFormat trackFormat) throws IllegalStateException {
        return 0;
    }

    @Override
    public void start() {

    }

    @Override
    public void writeSampleData(int trackIndex, @NonNull ByteBuffer data, @NonNull MediaCodec.BufferInfo bufferInfo) {

    }

    @Override
    public void stop() {

    }

    @Override
    public void release() {
        IOUtils.close(mOutputStream);
    }

    @Override
    public boolean isStarted() {
        return false;
    }
}
