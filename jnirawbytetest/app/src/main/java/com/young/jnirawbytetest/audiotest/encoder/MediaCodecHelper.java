package com.young.jnirawbytetest.audiotest.encoder;

import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.media.MediaCodec;
import android.os.Build;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

import java.nio.ByteBuffer;


/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-02-19
 * Time:   16:06
 * Life with Passion, Code with Creativity.
 */
@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
public final class MediaCodecHelper {
    private final MediaCodec mMediaCodec;
    private ByteBuffer[] mInputBuffer;
    private ByteBuffer[] mOutputBuffer;

    private final boolean IS_PRE_LOLLIPOP = Build.VERSION.SDK_INT < Build.VERSION_CODES.LOLLIPOP;

    public MediaCodecHelper(@NonNull MediaCodec mediaCodec) {
        mMediaCodec = mediaCodec;
    }

    /**
     * for pre-lollipop devices
     * called when init
     * {@link MediaCodec#INFO_OUTPUT_BUFFERS_CHANGED}
     */
    @SuppressWarnings("deprecation")
    public void fetchBuffers() {
        if (IS_PRE_LOLLIPOP) {
            mInputBuffer = mMediaCodec.getInputBuffers();
            mOutputBuffer = mMediaCodec.getOutputBuffers();
        }
    }

    /**
     * for pre-lollipop devices called when
     * {@link MediaCodec#INFO_OUTPUT_BUFFERS_CHANGED}
     */
    @SuppressWarnings("deprecation")
    public void changeOutputBuffers() {
        if (IS_PRE_LOLLIPOP) {
            mOutputBuffer = mMediaCodec.getOutputBuffers();
        }
    }

    @Nullable
    @SuppressLint("NewApi")
    @SuppressWarnings("deprecation")
    public ByteBuffer getInputBuffer(int index) {
        if (index < 0) {
            return null;
        }
        if (IS_PRE_LOLLIPOP) {
            return mInputBuffer[index];
        } else {
            return mMediaCodec.getInputBuffer(index);
        }
    }

    @Nullable
    @SuppressLint("NewApi")
    @SuppressWarnings("deprecation")
    public ByteBuffer getOutputBuffer(int index, @NonNull MediaCodec.BufferInfo info) {
        if (index < 0) {
            return null;
        }
        ByteBuffer buffer;
        if (IS_PRE_LOLLIPOP) {
            buffer = mOutputBuffer[index];
            if (buffer != null) {
                buffer.position(info.offset);
                buffer.limit(info.offset + info.size);
            }
        } else {
            buffer = mMediaCodec.getOutputBuffer(index);
        }

        return buffer;
    }
}
