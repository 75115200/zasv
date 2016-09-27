package com.young.jnirawbytetest.audiotest.encoder;

import android.media.MediaCodec;
import android.media.MediaFormat;
import android.support.annotation.NonNull;

import com.young.jnirawbytetest.IOUtils;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;

/**
 * Author: landerlyoung@gmail.com
 * Date:   2016-09-01
 * Time:   20:39
 * Life with Passion, Code with Creativity.
 */
public class AdtsAACMuxer implements AACMuxer {
    private static final String TAG = "AdtsAACMuxer";

    private final OutputStream mOutputStream;
    private final FileChannel mOutFileChannel;
    private ByteBuffer mAdtsHeaderByteBuffer;

    private final AdtsHeaderBuilder mAdtsHeaderBuilder = new AdtsHeaderBuilder();
    private boolean mTrackAdded;
    private boolean mStarted;

    private byte[] mArrayBuffer = null;

    public AdtsAACMuxer(@NonNull String filePath) throws IOException {
        mOutputStream = null;
        mOutFileChannel = new FileOutputStream(filePath).getChannel();
    }

    public AdtsAACMuxer(@NonNull OutputStream outputStream) {
        mOutputStream = outputStream;
        mOutFileChannel = null;
    }

    @Override
    public int addTrack(@NonNull MediaFormat trackFormat) throws IllegalStateException {
        if (mTrackAdded) {
            throw new IllegalStateException("Can only add one audio track");
        } else if (mStarted) {
            throw new IllegalStateException("Cannot add track after start");
        }
        mAdtsHeaderBuilder.setFromMediaFormat(trackFormat);
        return 0;
    }

    @Override
    public void start() {
        mStarted = true;
    }

    /**
     * {@inheritDoc}
     *
     * @throws IllegalArgumentException whenTrackIndex is not valid
     * @throws IllegalStateException when write aacFrame failed
     */
    @Override
    public void writeSampleData(int trackIndex, @NonNull ByteBuffer data,
                                @NonNull MediaCodec.BufferInfo bufferInfo)
            throws IllegalArgumentException, IllegalStateException {

        if (trackIndex != 0) {
            throw new IllegalArgumentException("invalid trackIndex:" + trackIndex);
        }
        if (bufferInfo.flags == MediaCodec.BUFFER_FLAG_CODEC_CONFIG) {
            //skip non-audio data
            return;
        }

        final int dataLen = data.remaining();
        mAdtsHeaderBuilder.setAudioFrameLength(dataLen, 1);

        try {
            if (mOutFileChannel != null) {
                if (mAdtsHeaderByteBuffer == null) {
                    mAdtsHeaderByteBuffer = ByteBuffer.wrap(mAdtsHeaderBuilder.getHeader());
                }
                mAdtsHeaderByteBuffer.position(0);
                mAdtsHeaderByteBuffer.limit(mAdtsHeaderBuilder.getHeaderLength());
                mOutFileChannel.write(mAdtsHeaderByteBuffer);

                mOutFileChannel.write(data);
            } else {
                final int headerLen = mAdtsHeaderBuilder.getHeaderLength();
                final int bufferLen = headerLen + dataLen;
                byte[] buffer = getBuffer(bufferLen);
                System.arraycopy(mAdtsHeaderBuilder.getHeader(), 0, buffer, 0, headerLen);
                data.get(buffer, headerLen, dataLen);

                mOutputStream.write(buffer, 0, bufferLen);
            }
        } catch (IOException e) {
            throw new IllegalStateException("write aac frame failed", e);
        }
    }

    @Override
    public void stop() {
        mStarted = false;
    }

    @Override
    public void release() {
        mStarted = false;
        IOUtils.close(mOutputStream);
        IOUtils.close(mOutFileChannel);
    }

    @Override
    public boolean isStarted() {
        return mStarted;
    }

    private byte[] getBuffer(int size) {
        if (mArrayBuffer == null || mArrayBuffer.length < size) {
            mArrayBuffer = new byte[size];
        }
        return mArrayBuffer;
    }
}
