package com.young.jnirawbytetest.audiotest.encoder;

import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaFormat;
import android.media.MediaMuxer;
import android.os.Build;
import android.support.annotation.NonNull;
import android.util.Log;

import com.young.jnirawbytetest.audiotest.logic.PCMFormat;

import java.io.IOException;
import java.nio.ByteBuffer;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-09-01
 * Time:   16:20
 * Life with Passion, Code with Creativity.
 */
@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
public class AACAudioEncoder {
    private static final String TAG = "AACAudioEncoder";

    private final MediaCodec mAudioEncoder;
    private final MediaCodec.BufferInfo mBufferInfo = new MediaCodec.BufferInfo();
    private final MediaCodecHelper mCodecHelper;

    //muxer
    private final AACMuxer mMediaMuxer;
    private int mMuxerTrackIndex;

    private static final long TIMEOUT_MILLIS = 10;

    @SuppressLint("InlinedApi")
    private static final String AAC_MIME_TYPE = MediaFormat.MIMETYPE_AUDIO_AAC;

    public AACAudioEncoder(@NonNull PCMFormat pcmFormat, @NonNull AACMuxer aacMuxer)
            throws IOException, IllegalArgumentException {
        mAudioEncoder = MediaCodec.createEncoderByType(AAC_MIME_TYPE);
        mCodecHelper = new MediaCodecHelper(mAudioEncoder);

        MediaFormat encodeFormat = new MediaFormat();
        encodeFormat.setString(MediaFormat.KEY_MIME, AAC_MIME_TYPE);
        encodeFormat.setInteger(MediaFormat.KEY_AAC_PROFILE, MediaCodecInfo.CodecProfileLevel.AACObjectLC);
        encodeFormat.setInteger(MediaFormat.KEY_SAMPLE_RATE, pcmFormat.sampleRate);
        encodeFormat.setInteger(MediaFormat.KEY_CHANNEL_COUNT, pcmFormat.getOutChannelCount());
        //128k
        encodeFormat.setInteger(MediaFormat.KEY_BIT_RATE, pcmFormat.bitRate);
        encodeFormat.setInteger(MediaFormat.KEY_MAX_INPUT_SIZE, pcmFormat.bufferSize);

        mAudioEncoder.configure(encodeFormat, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE);
        mAudioEncoder.start();

        mMediaMuxer = aacMuxer;
        mCodecHelper.fetchBuffers();
    }

    /**
     * @param data
     * @param length
     * @param sampleTimeUs
     * @param eos
     *
     * @return eos
     */
    public boolean writeData(byte[] data, int length, long sampleTimeUs, boolean eos) {
        while (!fillEncoder(data, length, sampleTimeUs, eos)) {
            drainEncoder(eos);
        }
        return eos;
    }

    private boolean fillEncoder(byte[] data, int length, long sampleTimeUs, boolean eos) {
        int encoderBufferIndex;
        ByteBuffer input;

        do {
            drainEncoder(false);
            encoderBufferIndex = mAudioEncoder.dequeueInputBuffer(TIMEOUT_MILLIS);
            input = mCodecHelper.getInputBuffer(encoderBufferIndex);
        } while (input == null);

        input.clear();
        Log.i(TAG, "fillEncoder: writeData len=" + length + " sampleTimeUs=" + sampleTimeUs);
        input.put(data);
        mAudioEncoder.queueInputBuffer(encoderBufferIndex, 0, length, sampleTimeUs,
                                       eos ? MediaCodec.BUFFER_FLAG_END_OF_STREAM : 0);
        return true;
    }

    /**
     * @param tillEOS drain till eos
     *
     * @return eos
     */
    @SuppressWarnings("deprecation")
    private boolean drainEncoder(boolean tillEOS) {
        while (true) {
            final int outBufIndex = mAudioEncoder.dequeueOutputBuffer(mBufferInfo, TIMEOUT_MILLIS);
            switch (outBufIndex) {
                case MediaCodec.INFO_TRY_AGAIN_LATER: {
                    Log.w(TAG, "drainEncoder: INFO_TRY_AGAIN_LATER");
                    if (!tillEOS) {
                        return false;
                    } else {
                        break;
                    }
                }
                case MediaCodec.INFO_OUTPUT_FORMAT_CHANGED: {
                    Log.i(TAG, "drainEncoder: INFO_OUTPUT_FORMAT_CHANGED");
                    if (!mMediaMuxer.isStarted()) {
                        MediaFormat trackFormat = mAudioEncoder.getOutputFormat();
                        mMuxerTrackIndex = mMediaMuxer.addTrack(trackFormat);

                        //start muxer
                        mMediaMuxer.start();
                    } else {
                        //fuck
                        Log.e(TAG, "drainEncoder: MediaCodec.INFO_OUTPUT_FORMAT_CHANGED:");
                        throw new IllegalStateException("format changed after muxer already started");
                    }
                    break;
                }
                case MediaCodec.INFO_OUTPUT_BUFFERS_CHANGED: {
                    Log.i(TAG, "drainEncoder: INFO_OUTPUT_BUFFERS_CHANGED");
                    mCodecHelper.fetchBuffers();
                    break;
                }
                default: {
                    if (!mMediaMuxer.isStarted()) {
                        throw new IllegalStateException("muxer is not started when get codec data");
                    }

                    //good to go
                    ByteBuffer outBuffer = mCodecHelper.getOutputBuffer(outBufIndex, mBufferInfo);

                    Log.i(TAG, "drainEncoder: writeSample " + mBufferInfo);

                    mMediaMuxer.writeSampleData(mMuxerTrackIndex, outBuffer, mBufferInfo);

                    outBuffer.clear();
                    mAudioEncoder.releaseOutputBuffer(outBufIndex, false);

                    if ((mBufferInfo.flags & MediaCodec.BUFFER_FLAG_END_OF_STREAM) != 0) {
                        //eos
                        return true;
                    }
                }
            }
        }
    }

    public void release() {
        mAudioEncoder.stop();
        mAudioEncoder.release();

        mMediaMuxer.stop();
        mMediaMuxer.release();

    }
}
