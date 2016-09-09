package com.young.jnirawbytetest.audiotest.encoder;

import android.support.annotation.NonNull;

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

    private int mBytePosition;
    private int mBitsPosition = 7;

    /**
     * @param bitsData byteOrder  is {@link ByteOrder#BIG_ENDIAN}
     *                 for example uint16_t x = 0x0a0b;
     *                 in big endian it will be [0a, 0b]; eg. 0a in addr 1000, 0b in addr 1001
     *                 in little endian it will be [0b, 0a]; eg. 0b in addr 1000, 0a in addr 1001
     */
    public BitsOperator(@NonNull byte[] bitsData) {
        mBitsData = bitsData;
        mBitsCount = bitsData.length * 8;
    }

    /**
     * @param bitsLen
     * @param data    big endian
     *
     * @return newPosition
     */
    public BitsOperator writeBits(int bitsLen, int data) {
        checkBounds(bitsLen);
        checkBitsLen(bitsLen);

        writeBitsBigEndian(bitsLen, data);
        return this;
    }

    /**
     * read bits and advance bits position
     *
     * @param bitsLen bitsCount to read
     *
     * @return val
     */
    public int readBits(int bitsLen) {
        checkBounds(bitsLen);
        checkBitsLen(bitsLen);

        return readBitsBigEndian(bitsLen);
    }

    /**
     * read bits but don't move bits position
     *
     * @see #readBits(int)
     */
    public int showBits(int bitsLen) {
        int val = readBits(bitsLen);

        relativeSeek(-bitsLen);
        return val;
    }

    public BitsOperator seekToBits(int bitsFromStart) {
        if (bitsFromStart > mBitsCount) {
            throw new IndexOutOfBoundsException();
        }

        mBytePosition = 0;
        mBitsPosition = 7;
        relativeSeek(bitsFromStart);

        return this;
    }

    public BitsOperator relativeSeek(int bitsCount) {
        checkBounds(bitsCount);

        int posInBits = mBytePosition * 8 + (7 - mBitsPosition);
        posInBits += bitsCount;

        mBytePosition = posInBits / 8;
        mBitsPosition = 7 - (posInBits % 8);

        return this;
    }

    public BitsOperator alignToNextByte() {
        if (mBitsPosition < 7) {
            if (mBytePosition + 1 >= mBitsData.length) {
                throw new IndexOutOfBoundsException();
            }

            mBytePosition++;
            mBitsPosition = 7;
        }
        return this;
    }

    public int getBitsPosition() {
        return mBytePosition * 8 + (7 - mBitsPosition);
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

    public BitsOperator clearAll() {
        for (int i = 0; i < mBitsData.length; i++) {
            mBitsData[i] = 0;
        }
        return rewind();
    }

    public BitsOperator rewind() {
        mBitsPosition = 7;
        mBytePosition = 0;

        return this;
    }

    //private impl
    private void checkBounds(int offset) {
        int i = getBitsPosition() + offset;
        if (i < 0 || i >= getBitsCount()) {
            throw new IndexOutOfBoundsException(
                    "current position=" + getBitsPosition()
                            + " offset=" + offset
                            + " bitsCount=" + getBitsCount()
            );
        }
    }

    private void checkBitsLen(int bitsLen) {
        if (bitsLen > 32) {
            throw new IllegalArgumentException("bitsLen > 32");
        } else if (bitsLen < 0) {
            throw new IllegalArgumentException("bitsLen <0");
        }
    }

    //high bits first
    private void writeBitsBigEndian(int bitsLen, int data) {
        data <<= (32 - bitsLen);

        while (bitsLen > 0) {
            int bitsToWrite = Math.min(bitsLen, mBitsPosition + 1);
            //catch the highest byte
            byte val = (byte) (data >>> (32 - 8));

            if (bitsToWrite < 8) {
                val = (byte) ((val & 0xff) >>> (8 - bitsToWrite));
            }

            //move to write pos
            val <<= mBitsPosition + 1 - bitsToWrite;

            //clear dst bits before write
            byte clearMask = -1; //0xffff_ffff_ffff_ffff
            clearMask <<= 8 - bitsToWrite;
            clearMask = (byte) ((clearMask & 0xff) >>> (8 - bitsToWrite));
            clearMask = (byte) (clearMask << (mBitsPosition + 1 - bitsToWrite));
            clearMask = (byte) ~clearMask;

            mBitsData[mBytePosition] &= clearMask;


            mBitsData[mBytePosition] |= val;

            data <<= bitsToWrite;

            bitsLen -= bitsToWrite;
            relativeSeek(bitsToWrite);
        }
    }

    private int readBitsBigEndian(int bitsCount) {
        int ret = 0;

        int readPos = 31;
        while (bitsCount > 0) {
            int bitsToRead = Math.min(bitsCount, mBitsPosition + 1);

            //catch the valid value
            byte byteVal = mBitsData[mBytePosition];

            int bitsTaken = mBitsPosition + 1;
            if (bitsTaken < 8) {
                //clear high bits
                byteVal <<= (8 - bitsTaken);
                byteVal = (byte) ((byteVal & 0xff) >>> (8 - bitsTaken));
            }

            //to normal pos
            int val = (byteVal & 0xff) >>> (mBitsPosition + 1 - bitsToRead);

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

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (byte b : mBitsData) {
            String str = Integer.toBinaryString(b & 0xff);
            for (int i = 0; i < 8 - str.length(); i++) {
                sb.append('0');
            }
            sb.append(str);

            sb.insert(sb.length() - 4, "_");
            sb.append(' ');
        }
        return sb.toString();
    }
}
