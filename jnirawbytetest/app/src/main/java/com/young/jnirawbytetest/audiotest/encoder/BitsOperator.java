package com.young.jnirawbytetest.audiotest.encoder;

import android.support.annotation.NonNull;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-09-02
 * Time:   11:06
 * Life with Passion, Code with Creativity.
 */
public final class BitsOperator {
    private final byte[] mBitsData;
    private final int mBitsCount;
    private final ByteOrder mByteOrder;

    private int mBytePosition;
    private int mBitsPosition;

    /**
     * @param bitsData
     * @param byteOrder default is {@link ByteOrder#BIG_ENDIAN}
     *                  for example uint16_t x = 0x0a0b;
     *                  in big endian it will be [0a, 0b]; eg. 0a in addr 1000, 0b in addr 1001
     *                  in little endian it will be [0b, 0a]; eg. 0b in addr 1000, 0a in addr 1001
     */
    public BitsOperator(@NonNull byte[] bitsData, @NonNull ByteOrder byteOrder) {
        mBitsData = bitsData;
        mBitsCount = bitsData.length * 8;
        mByteOrder = byteOrder;
    }

    public BitsOperator(@NonNull byte[] bitsData) {
        this(bitsData, ByteOrder.BIG_ENDIAN);
    }

    /**
     * @param bitsLen
     * @param data    big endian
     *
     * @return newPosition
     */
    public void writeBits(int bitsLen, int data) {
        checkBounds(bitsLen);
        checkBitsLen(bitsLen);

        if (mByteOrder == ByteOrder.BIG_ENDIAN) {
            writeBitsBigEndian(bitsLen, data);
        } else {
            writeBitsLittleEndian(bitsLen, data);
        }
    }

    /**
     * read bits and advance bits position
     *
     * @param bitsLen bitsCount to read
     *
     * @return val
     */
    public int readBits(int bitsLen) {
        if (mByteOrder == ByteOrder.BIG_ENDIAN) {
            return readBitsBigEndian(bitsLen);
        } else {
            return readBitsLittleEndian(bitsLen);
        }
    }

    /**
     * read bits but don't advance bits position
     *
     * @see #readBits(int)
     */
    public int showBits(int bitsLen) {
        checkBounds(bitsLen);
        checkBitsLen(bitsLen);

        int val = readBits(bitsLen);

        relativeSeek(-bitsLen);

        return val;
    }

    public void seekToBits(int bitsFromStart) {
        if (bitsFromStart > mBitsCount) {
            throw new IndexOutOfBoundsException();
        }

        mBitsPosition = 0;
        mBytePosition = 0;
        relativeSeek(bitsFromStart);
    }

    public void relativeSeek(int bitsCount) {
        checkBounds(bitsCount);

        int posInBits = mBytePosition * 8 + mBitsPosition;
        posInBits += bitsCount;

        mBitsPosition = posInBits % 8;
        mBytePosition = posInBits / 8;
    }

    public void alignToNextByte() {
        if (mBitsPosition > 0) {
            if (mBytePosition == mBitsData.length) {
                throw new IndexOutOfBoundsException();
            }

            mBytePosition++;
            mBitsPosition = 0;
        }
    }

    public int getBitsPosition() {
        return mBytePosition * 8 + mBitsPosition;
    }

    public int getBitsLeft() {
        return mBitsCount - getBitsPosition();
    }

    public int getBitsCount() {
        return mBitsCount;
    }

    public byte[] getBits() {
        return mBitsData;
    }

    public void clear() {
        for (int i = 0; i < mBitsData.length; i++) {
            mBitsData[i] = 0;
        }
        rewind();
    }

    public void rewind() {
        mBitsPosition = 0;
        mBytePosition = 0;
    }

    //private impl
    private void checkBounds(int offset) {
        int i = getBitsPosition() + offset;
        if (i < 0 || i >= getBitsCount()) {
            throw new IndexOutOfBoundsException("current position=" + getBitsPosition() + " offset=" + offset);
        }
    }

    private void checkBitsLen(int bitsLen) {
        if (bitsLen > 32) {
            throw new IllegalArgumentException("bitsLen > 32");
        } else if (bitsLen < 0) {
            throw new IllegalArgumentException("bitsLen <0");
        }
    }

    //lower bits first
    private void writeBitsLittleEndian(int bitsLen, int data) {
        while (bitsLen > 0) {
            int bitsToWrite = Math.min(bitsLen, 8 - mBitsPosition);
            //catch the lowest byte
            byte val = (byte) (data & 0xff);

            //erase high zero
            val <<= mBitsPosition;
            mBitsData[mBytePosition] |= val;
            data >>>= bitsToWrite;

            bitsLen -= bitsToWrite;
            relativeSeek(bitsToWrite);
        }
    }

    //high bits first
    private void writeBitsBigEndian(int bitsLen, int data) {
        data <<= (32 - bitsLen);

        while (bitsLen > 0) {
            int bitsToWrite = Math.min(bitsLen, 8 - mBitsPosition);
            //catch the highest byte
            byte val = (byte) ((data >>> (32 - 8)) & 0xff);

            val >>>= mBitsPosition;
            mBitsData[mBytePosition] |= val;

            data <<= bitsToWrite;

            bitsLen -= bitsToWrite;
            relativeSeek(bitsToWrite);
        }
    }

    private int readBitsLittleEndian(int bitsCount) {
        int ret = 0;

        int readPos = 0;
        while (bitsCount > 0) {
            int bitsToRead = Math.min(bitsCount, 8 - mBitsPosition);

            //catch the valid value
            byte byteVal = mBitsData[mBytePosition];

            //bit we are use, include the bit before position
            final int takenBitsCount = bitsCount + mBitsPosition;
            if (takenBitsCount < 8) {
                //clear high bits
                byteVal <<= (8 - takenBitsCount);
                byteVal >>>= (8 - takenBitsCount);
            }

            int val = byteVal & 0xff;

            //to normal pos
            //erase bits before position
            val >>>= mBitsPosition;

            //to fill the ret data
            val <<= readPos;

            ret |= val;

            readPos += bitsToRead;
            bitsCount -= bitsToRead;
            relativeSeek(bitsToRead);
        }
        return ret;
    }

    private int readBitsBigEndian(int bitsCount) {
        int ret = 0;

        int readPos = 31;
        while (bitsCount > 0) {
            int bitsToRead = Math.min(bitsCount, 8 - mBitsPosition);

            //catch the valid value
            int val = mBitsData[mBytePosition];

            //to normal pos
            val >>>= mBitsPosition;

            //we are writing top -> down
            //move pos down before write
            readPos -= bitsToRead;
            //to fill the ret data
            val <<= readPos;

            ret |= val;

            bitsCount -= bitsToRead;
            relativeSeek(bitsToRead);
        }

        //back to normal
        ret >>>= readPos;
        return ret;
    }

}
