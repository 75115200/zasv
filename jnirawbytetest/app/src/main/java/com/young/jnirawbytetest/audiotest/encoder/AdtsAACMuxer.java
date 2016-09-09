package com.young.jnirawbytetest.audiotest.encoder;

import android.media.MediaCodec;
import android.media.MediaFormat;
import android.support.annotation.NonNull;
import android.test.MoreAsserts;
import android.util.Log;

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
    private static final String TAG = "AdtsAACMuxer";

    private final OutputStream mOutputStream;

    private final AdtsHeaderBuilder mAdtsHeaderBuilder;
    private boolean mTrackAdded;
    private boolean mStarted;

    private byte[] mBuffer = new byte[1024 * 8];

    public AdtsAACMuxer(@NonNull String filePath) throws IOException {
        this(new BufferedOutputStream(new FileOutputStream(filePath)));
    }

    public AdtsAACMuxer(@NonNull OutputStream outputStream) {
        mOutputStream = outputStream;
        mAdtsHeaderBuilder = new AdtsHeaderBuilder();
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
    public void writeSampleData(int trackIndex, @NonNull ByteBuffer data, @NonNull MediaCodec.BufferInfo bufferInfo)
            throws IllegalArgumentException, IllegalStateException {
        if (trackIndex != 0) {
            throw new IllegalArgumentException("invalid trackIndex:" + trackIndex);
        }
        if (bufferInfo.flags == MediaCodec.BUFFER_FLAG_CODEC_CONFIG) {
            //skip non-audio data
            return;
        }

        final int headerLen = mAdtsHeaderBuilder.getHeaderLength();
        final int dataLen = data.remaining();
        Log.e(TAG, "before=" + mAdtsHeaderBuilder);
        mAdtsHeaderBuilder.setAudioFrameLength(dataLen, 1);
        Log.e(TAG, "after =" + mAdtsHeaderBuilder + " exp=" + (7 + dataLen));

        final int bufferLen = headerLen + dataLen;
        byte[] buffer = getBuffer(bufferLen);
        System.arraycopy(mAdtsHeaderBuilder.getHeader(), 0, buffer, 0, headerLen);
        data.get(buffer, headerLen, dataLen);

        int frameLen;
        BitsOperator op = new BitsOperator(mAdtsHeaderBuilder.getHeader());
        Log.i(TAG, "SyncWord=" + Integer.toBinaryString(op.readBits(12))
                + "\nMPEG Version=" + Integer.toBinaryString(op.readBits(1))
                + "\nLayer=" + Integer.toBinaryString(op.readBits(2))
                + "\ncrc=" + Integer.toBinaryString(op.readBits(1))
                + "\nprofile-1=" + Integer.toBinaryString(op.readBits(2))
                + "\nfreq=" + Integer.toBinaryString(op.readBits(4))
                + "\nomit=" + Integer.toBinaryString(op.readBits(1))
                + "\nchannel=" + Integer.toBinaryString(op.readBits(3))
                + "\nomit=" + Integer.toBinaryString(op.readBits(1))
                + "\nomit=" + Integer.toBinaryString(op.readBits(1))
                + "\nomit=" + Integer.toBinaryString(op.readBits(1))
                + "\nomit=" + Integer.toBinaryString(op.readBits(1))
                + "\nframeLen=" + Integer.toBinaryString(frameLen = op.readBits(13))
                /**/ + "--" + frameLen + " exp=" + Integer.toBinaryString(bufferLen) + "--" + bufferLen
                + "\nbufferFullness=" + Integer.toBinaryString(op.readBits(11))
                + "\naacFrameCount=" + Integer.toBinaryString(op.readBits(2))
                + "\nallBits=" + mAdtsHeaderBuilder
        );

        try {
            mOutputStream.write(buffer, 0, bufferLen);
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
    }

    @Override
    public boolean isStarted() {
        return mStarted;
    }

    private byte[] getBuffer(int size) {
        if (mBuffer == null || mBuffer.length < size) {
            mBuffer = new byte[size];
        }
        return mBuffer;
    }
}
