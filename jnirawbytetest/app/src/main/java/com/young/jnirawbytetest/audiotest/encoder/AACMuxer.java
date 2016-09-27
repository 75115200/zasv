package com.young.jnirawbytetest.audiotest.encoder;

import android.media.MediaCodec;
import android.media.MediaFormat;
import android.support.annotation.NonNull;

import java.nio.ByteBuffer;

/**
 * Author: landerlyoung@gmail.com
 * Date:   2016-09-01
 * Time:   19:38
 * Life with Passion, Code with Creativity.
 */
public interface AACMuxer {

    /**
     * @param trackFormat media format for this track
     * @return trackIndex
     * @throws IllegalStateException when you add track after muxer start
     */
    int addTrack(@NonNull MediaFormat trackFormat) throws IllegalStateException;

    void start();

    void writeSampleData(int trackIndex, @NonNull ByteBuffer data, @NonNull MediaCodec.BufferInfo bufferInfo);

    void stop();

    void release();

    boolean isStarted();

}
