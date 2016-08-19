package com.young.jnirawbytetest.audiotest.logic;

import android.os.Bundle;
import android.support.annotation.NonNull;

import java.nio.ByteBuffer;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-10
 * Time:   15:47
 * Life with Passion, Code with Creativity.
 */
public interface AudioProducer {

    /**
     * @param data
     * @param offset
     * @param len
     * @param param
     */
    void read(@NonNull byte[] data, int offset, int len, @NonNull Bundle param);

    /**
     * @param data
     * @param param
     */
    void read(@NonNull ByteBuffer data, @NonNull Bundle param);

    void release();
}
