package com.young.jnirawbytetest.audiotest.encoder;

import android.annotation.TargetApi;
import android.media.MediaFormat;
import android.os.Build;
import android.support.annotation.NonNull;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-09-01
 * Time:   20:48
 * Life with Passion, Code with Creativity.
 * <p>
 * <a href="https://wiki.multimedia.cx/index.php?title=ADTS"> see here </a>
 */
@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
public final class AdtsHeaderBuilder {

    public static final int ADTS_MAX_FRAME_SIZE = (1 << 13) - 1;

    private static final String KEY_AAC_AUDIO_SPECIFIC_CONFIG = "csd-0";

    /**
     * 11 bits
     * Buffer fullness
     * <p>
     * don't know what it is...
     * however ffpmeg hardcoded it as 0x7ff
     */
    public static final int BUFFER_FULLNESS = 0x7ff;

    private boolean mHasCrc = false;

    private final BitsOperator mAdts = new BitsOperator(new byte[9]);

    public AdtsHeaderBuilder() {
        //buildSyncWord
        mAdts.seekToBits(0).writeBits(12, 0xfff)
             //layer
             .seekToBits(13).writeBits(2, 0)
             //fixed bits
             .seekToBits(22).writeBits(1, 0)
             .seekToBits(26).writeBits(4, 0)
             .seekToBits(43).writeBits(11, BUFFER_FULLNESS);

        setCrcProtection(false, (short) 0);
    }

    public void setFromMediaFormat(@NonNull MediaFormat format)
            throws IllegalArgumentException {

        if (format.containsKey(KEY_AAC_AUDIO_SPECIFIC_CONFIG)) {
            ByteBuffer csd = format.getByteBuffer(KEY_AAC_AUDIO_SPECIFIC_CONFIG);
            byte[] data = new byte[6];
            csd.get(data, 0, Math.min(csd.remaining(), data.length));
            csd.rewind();
            setFromAudioSpecificConfig(data);
        } else {
            throw new IllegalArgumentException("format does not contains csd-0");
        }
    }


    public void setFromAudioSpecificConfig(byte[] data) {
        BitsOperator op = new BitsOperator(data);

        int objType = op.readBits(5);
        if (objType == 31) {
            objType += op.readBits(6);
        }
        //MPEG-4 AudioObjectType - 1
        mAdts.seekToBits(16).writeBits(2, objType - 1);

        int freqIndex = op.readBits(4);
        if (freqIndex == 15) {
            throw new IllegalArgumentException("frequencyIndex 15 is forbidden for adts");
        }
        mAdts.seekToBits(18).writeBits(4, freqIndex);

        int channelConfig = op.readBits(4);
        mAdts.seekToBits(23).writeBits(3, channelConfig);
    }

    /**
     * must be called after {@link #setCrcProtection(boolean, short)}
     *
     * @param aacFrameLength how long this frame is
     * @param aacFrameCount  how many aac frame it contains. ALWAYS be 1.
     */
    public void setAudioFrameLength(int aacFrameLength, int aacFrameCount) {
        aacFrameLength += getHeaderLength();

        if (aacFrameLength > ADTS_MAX_FRAME_SIZE) {
            throw new IllegalArgumentException(
                    "length(" + aacFrameLength +
                            ") + headerLen(" + getHeaderLength() +
                            ") > ADTS_MAX_FRAME_SIZE(" + ADTS_MAX_FRAME_SIZE + ")");
        }

        mAdts.seekToBits(30).writeBits(13, aacFrameLength)
             .seekToBits(54).writeBits(2, aacFrameCount);
    }

    public void setCrcProtection(boolean hasCrc, short protectBits) {
        mHasCrc = hasCrc;

        mAdts.seekToBits(15).writeBits(1, hasCrc ? 0 : 1);

        if (hasCrc) {
            mAdts.seekToBits(56).writeBits(16, protectBits);
        }
    }

    /**
     * @return header len in byte.
     * 9 if there is 2-byte crc procection,
     * 7 for no-crc.
     */
    public int getHeaderLength() {
        return mHasCrc ? 9 : 7;
    }

    public byte[] getHeader() {
        return mAdts.getBits();
    }
}
