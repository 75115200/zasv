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
    private final byte[] mBits;
    private final int mBitsCount;
    private final ByteOrder mByteOrder;

    private int mBytePosition;
    private int mBitsPosition;

    /**
     * @param bits
     * @param byteOrder default is {@link ByteOrder#BIG_ENDIAN}
     */
    public BitsOperator(@NonNull byte[] bits, @NonNull ByteOrder byteOrder) {
        mBits = bits;
        mBitsCount = bits.length * 8;
        mByteOrder = byteOrder;
    }

    public BitsOperator(@NonNull byte[] bits) {
        this(bits, ByteOrder.BIG_ENDIAN);
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
        int val = showBits(bitsLen);
        skipBits(bitsLen);
        return val;
    }

    /**
     * read bits but don't advance bits position
     *
     * @see #readBits(int)
     */
    public int showBits(int bitsLen) {
        checkBounds(bitsLen);
        checkBitsLen(bitsLen);

        if (mByteOrder == ByteOrder.BIG_ENDIAN) {
            return showBitsBigEndian(bitsLen);
        } else {
            return showBitsLittleEndian(bitsLen);
        }
    }

    public void seekToBits(int bitsFromStart) {
        if (bitsFromStart > mBitsCount) {
            throw new IndexOutOfBoundsException();
        }

        mBitsPosition = 0;
        mBytePosition = 0;
        skipBits(bitsFromStart);
    }

    public void skipBits(int bitsCount) {
        checkBounds(bitsCount);

        mBitsPosition += bitsCount;
        mBytePosition = mBitsPosition / 8;
        mBitsPosition %= 8;
    }

    public void alignToNextByte() {
        if (mBitsPosition > 0) {
            if (mBytePosition == mBits.length) {
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
        return mBits;
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
        }
    }

    private void writeBitsBigEndian(int bitsLen, int data) {

    }

    private void writeBitsLittleEndian(int bitsLen, int data) {
    }

    private int showBitsBigEndian(int bitsCount) {
        return 0;
    }

    private int showBitsLittleEndian(int bitsCount) {
        return 0;
    }

}
