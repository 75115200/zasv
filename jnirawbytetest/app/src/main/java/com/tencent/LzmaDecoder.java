package com.tencent;

import android.support.annotation.NonNull;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import SevenZip.Compression.LZMA.Decoder;

/**
 * <pre>
 * Author: taylorcyang@tencent.com
 * Date:   2017-02-13
 * Time:   20:13
 * Life with Passion, Code with Creativity.
 * </pre>
 */
public class LzmaDecoder {

    public static void decode(@NonNull InputStream inStream, @NonNull OutputStream outStream) throws IOException {
        final int propertiesSize = 5;
        final int streamSizeLen = 8;
        final byte[] buffer = new byte[streamSizeLen];

        if (inStream.read(buffer, 0, propertiesSize) != propertiesSize) {
            throw new IOException("input .lzma file is too short");
        }

        Decoder decoder = new Decoder();
        if (!decoder.SetDecoderProperties(buffer)) {
            throw new IOException("Incorrect stream properties");
        }

        long outSize = 0L;

        if (inStream.read(buffer) == -1) {
            throw new IOException("Can\'t read stream size");
        }

        // little endian int64_t
        for (int i = 0; i < streamSizeLen; ++i) {
            outSize |= (long) (buffer[i] & 0xff) << 8 * i;
        }

        if (!decoder.Code(inStream, outStream, outSize)) {
            throw new IOException("Error in data stream");
        }
    }
}
