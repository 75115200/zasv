package com.young.jnirawbytetest.audiotest.encoder;

import android.annotation.TargetApi;
import android.media.MediaCodec;
import android.media.MediaFormat;
import android.media.MediaMuxer;
import android.os.Build;
import android.support.annotation.NonNull;

import java.io.IOException;
import java.nio.ByteBuffer;

/**
 * Author: landerlyoung@gmail.com
 * Date:   2016-09-01
 * Time:   19:56
 * Life with Passion, Code with Creativity.
 */
@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR2)
public class DroidM4AMuxer implements AACMuxer {

    private final MediaMuxer mMediaMuxer;
    private boolean mIsStarted;

    public DroidM4AMuxer(String filePath) throws IOException{
        mMediaMuxer = new MediaMuxer(filePath, MediaMuxer.OutputFormat.MUXER_OUTPUT_MPEG_4);
    }

    @Override
    public int addTrack(@NonNull MediaFormat trackFormat)
            throws IllegalStateException{
        if (mIsStarted) {
            throw new IllegalStateException("can't add track after muxer started");
        }
        return mMediaMuxer.addTrack(trackFormat);
    }

    @Override
    public void start() {
        mIsStarted = true;
        mMediaMuxer.start();
    }

    @Override
    public void writeSampleData(int trackIndex, @NonNull ByteBuffer data, @NonNull MediaCodec.BufferInfo bufferInfo) {
        mMediaMuxer.writeSampleData(trackIndex, data, bufferInfo);
    }

    @Override
    public void stop() {
        mMediaMuxer.stop();
        mIsStarted = false;
    }

    @Override
    public void release() {
        mMediaMuxer.release();
        mIsStarted = false;
    }

    @Override
    public boolean isStarted() {
        return mIsStarted;
    }
}
