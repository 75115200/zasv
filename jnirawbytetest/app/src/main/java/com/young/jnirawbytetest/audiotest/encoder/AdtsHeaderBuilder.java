package com.young.jnirawbytetest.audiotest.encoder;

import android.media.MediaFormat;
import android.support.annotation.NonNull;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-09-01
 * Time:   20:48
 * Life with Passion, Code with Creativity.
 * <p>
 * <a href="https://wiki.multimedia.cx/index.php?title=ADTS"> see here </a>
 */

public final class AdtsHeaderBuilder {
    /**
     * 0-15
     * 0 1 2 3 4 5 6 7    8 9 a b c d e f
     * +-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+-+
     * |1|1|1|1|1|1|1|1|  |1|1|1|1| |0|0| |
     * +-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+-+
     * ------ syncword  0xffff -- ↓     ↓
     * ↓     0:NO-CRC 1:CRC
     * 0:MPEG-4 1:MPEG-2
     * <p>
     * 16-31
     * 0 1 2 3 4 5 6 7    8 9 a b c d e f
     * +-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+-+
     * | | | | | | | | |  | | | | | | | | |
     * +-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+-+
     * <p>
     * <p>
     * 32-47
     * 0 1 2 3 4 5 6 7    8 9 a b c d e f
     * +-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+-+
     * | | | | | | | | |  | | | | | | | | |
     * +-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+-+
     * <p>
     * 48-63
     * 0 1 2 3 4 5 6 7    8 9 a b c d e f
     * +-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+-+
     * | | | | | | | | |  | | | | | | | | |
     * +-+-+-+-+-+-+-+-+  +-+-+-+-+-+-+-+-+
     */
    final byte[] mAdtsHeader = new byte[9];

    public static final int ADTS_MAX_FRAME_SIZE = (1 << 13) - 1;

    /**
     *12 bits
     *syncword 0xFFF, all bits must be 1
     */

    /**
     * 1 bit
     * MPEG Version: 0 for MPEG-4, 1 for MPEG-2
     */
    private boolean mIsMpeg4;

    /**
     * 1bit
     * protection absent, Warning, set to 1 if there is no CRC and 0 if there is CRC
     */
    private boolean mHasProtection;

    private short mCrcCheckSum;

    /**
     * 2 bits
     * profile, the <a href="https://wiki.multimedia.cx/index.php?title=MPEG-4_Audio#Audio_Object_Types">MPEG-4 Audio Object Type </a>minus 1
     */
    private byte mMpeg4AudioObjectTypeMinusOne;

    /**
     * 4 bits
     * <a href="https://wiki.multimedia.cx/index.php?title=MPEG-4_Audio#Sampling_Frequencies">MPEG-4 Sampling Frequency Index</a> (15 is forbidden)
     */
    private byte mMPEG4SampleFrequencyIndex;

    /**
     * 3 bits
     * <a href="https://wiki.multimedia.cx/index.php?title=MPEG-4_Audio#Channel_Configurations">MPEG-4 Channel Configuration</a>
     * (in the case of 0, the channel configuration is sent via an inband PCE)
     */
    private byte mMPEG4ChannelConfig;

    /**
     * 13 bits
     * frame length, this value must include 7 or 9 bytes of header length:
     * FrameLength = (ProtectionAbsent == 1 ? 7 : 9) + size(AACFrame)
     */
    private short mFrameLength;

    /**
     * 11 bits
     * Buffer fullness
     * <p>
     * don't know what it is...
     * however ffpmeg hardcoded it as 0x7ff
     * 0x7ff
     */
    private short mBufferFullness = 0x7ff;

    /**
     * 2 bits
     * Number of AAC frames (RDBs) in ADTS frame minus 1,
     * for maximum compatibility always use 1 AAC frame per ADTS frame
     */
    private byte mAACFramesMinuxOne;


    /**
     * @param isMPEG4 is MPEG-4 or MPEG-2
     */
    public AdtsHeaderBuilder setMPEGVersion(boolean isMPEG4) {
        mIsMpeg4 = isMPEG4;
        return this;
    }

    public AdtsHeaderBuilder setHasCrcProtection(boolean hasCrcProtection, short crcCheckSum) {
        mHasProtection = hasCrcProtection;
        mCrcCheckSum = crcCheckSum;
        return this;
    }

    private AdtsHeaderBuilder() {
        buildSyncWord();
    }

    private void buildSyncWord() {
        //12 syncword
        mAdtsHeader[0] = (byte) 0xff;
        mAdtsHeader[1] = (byte) 0xf0;
    }

    public AdtsHeaderBuilder(@NonNull MediaFormat format) {
        setFromMediaFormat(format);
    }

    public void setFromMediaFormat(@NonNull MediaFormat format) {

    }
}
