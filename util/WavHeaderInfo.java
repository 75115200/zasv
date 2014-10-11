package com.young.format;

/**
 * Author: landerlyoung
 * Date:   2014-10-11
 * Time:   14:38
 * Life with passion. Code with creativity!
 * wav file format parser.
 * wav header information: <a href="https://ccrma.stanford.edu/courses/422/projects/WaveFormat/" >here</a>
 * So this class support only too sub-chunk information: "fmt " and "data"
 */
public class WavHeaderInfo {
    private WavHeaderInfo() {
    }

    public RIFF_Chunk mRiffChunk;
    public FMT_Chunk mFmtChunk;
    public DATA_Chunk mDataChunk;

    public static WavHeaderInfo create(byte[] data) {
        return create(data, 0, data.length);
    }

    /**
     * @param data
     * @param offset
     * @param len
     * @return
     */
    public static WavHeaderInfo create(byte[] data, int offset, int len) {
        return null;
    }

    /**
     * For why plus 8, refer to {@link RIFF_Chunk#ChunkSize}.
     *
     * @return total file size
     */
    public int getFileSize() {
        return mRiffChunk.ChunkSize + 8;
    }

    public int getHeaderSize() {
        return getFileSize() - getDataSize();
    }

    public int getDataSize() {
        return mDataChunk.Subchunk2Size;
    }

    public static class RIFF_Chunk {

        //*************start of "RIFF" chunk***************
        /**
         * ChunkID ie: string of "RIFF"
         */
        public static final byte[] ChunkID = {
                'R', 'I', 'F', 'F',
        };

        /**
         * 36 + SubChunk2Size, or more precisely:
         * 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
         * This is the size of the rest of the chunk
         * following this number.  This is the size of the
         * entire file in bytes minus 8 bytes for the
         * two fields not included in this count:
         * ChunkID and ChunkSize.
         */
        public int ChunkSize;

        public static final byte[] Fotmat = {
                'W', 'A', 'V', 'E',
        };

        //**************end of riff chunk*****************
    }

    public static class FMT_Chunk {


        //************start of "fmt " sub-chunk***********
        public static final byte[] subchunk1ID = {
                'f', 'm', 't', ' '//a space
        };

        /**
         * 16 for PCM.  This is the size of the
         * rest of the Subchunk which follows this number.
         */
        public int Subchunk1Size;

        /**
         * AudioFormat PCM = 1 (i.e. Linear quantization)
         * <br/>
         * Values other than 1 indicate some
         * form of compression.
         */
        public short AudioFormat;

        /**
         * NumChannels  Mono = 1, Stereo = 2, etc.
         *
         * @see #NumChannels_Mono
         * @see #NumChannels_Stereo
         */
        public short NumChannels;

        /**
         * SampleRate 8000, 44100, etc.
         */
        public int SampleRate;

        /**
         * ByteRate == SampleRate * NumChannels * BitsPerSample/8
         */
        public int ByteRate;

        /**
         * BlockAlign == NumChannels * BitsPerSample/8
         * <br/>
         * The number of bytes for one sample including
         * all channels. I wonder what happens when
         * this number isn't an integer?
         */
        public short BlockAlign;

        /**
         * BitsPerSample 8 bits = 8, 16 bits = 16, etc.
         */
        public short BitsPerSample;
        //*************end of "fmt " sub-chunk***********

        //============constance of field==================
        /**
         * constance of {@link #AudioFormat}
         */
        public static final short AudioFormat_PCM = 1;

        /**
         * constance of {@link #NumChannels}
         *
         * @see #NumChannels
         * @see #NumChannels_Stereo
         */
        public static final short NumChannels_Mono = 1;
        /**
         * constance of {@link #NumChannels}
         *
         * @see #NumChannels
         * @see #NumChannels_Mono
         */
        public static final short NumChannels_Stereo = 2;
        //=================================================
    }

    public static class DATA_Chunk {
        //***********start of "data" sub-chunk***********
        public static final byte[] Subchunk2ID = {
                'd', 'a', 't', 'a',
        };

        /**
         * Subchunk2Size == NumSamples * NumChannels * BitsPerSample/8
         * <br/>
         * This is the number of bytes in the data.
         * You can also think of this as the size
         * of the read of the subchunk following this
         * number.
         */
        public int Subchunk2Size;

        //***********start of "data" sub-chunk***********
    }
}
