package com.young.jnirawbytetest;

import com.young.jnirawbytetest.audiotest.encoder.BitsOperator;

import org.junit.Test;

import java.nio.ByteOrder;

import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class ExampleUnitTest {
    @Test
    public void addition_isCorrect() throws Exception {
        assertEquals(4, 2 + 2);
    }

    @Test
    public void testLittleEndian() throws Exception {
        BitsOperator op = new BitsOperator(new byte[8], ByteOrder.LITTLE_ENDIAN);

        run(op);
    }

    @Test
    public void testBigEndian() throws Exception {
        BitsOperator op = new BitsOperator(new byte[8]);

        run(op);
    }

    private void run(BitsOperator op) {
        op.writeBits(12, 0x123);

        op.rewind();

        assertEquals(0x123, op.showBits(12));
        assertEquals(0x123, op.readBits(12));
        assertNotEquals(0x123, op.showBits(12));

        op.writeBits(3, 0b101);
        op.writeBits(2, 0b10);
        op.writeBits(7, 0b1101101);
        op.writeBits(16, 0x1234);
        op.writeBits(3, 0b101);
        op.writeBits(3, 0b001);
        op.writeBits(3, 0b111);
        op.writeBits(3, 0b100);

        op.rewind();

        assertEquals(0x123, op.readBits(12));
        assertEquals(0b101, op.readBits(3));
        assertEquals(0b10, op.readBits(2));
        assertEquals(0b1101101, op.readBits(7));
        assertEquals(0x1234, op.readBits(16));

        assertEquals(0b101, op.readBits(3));
        assertEquals(0b001, op.readBits(3));
        assertEquals(0b111, op.readBits(3));
        assertEquals(0b100, op.readBits(3));
    }

}