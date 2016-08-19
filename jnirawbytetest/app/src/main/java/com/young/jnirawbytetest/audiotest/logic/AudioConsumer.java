package com.young.jnirawbytetest.audiotest.logic;

import android.os.Bundle;
import android.support.annotation.NonNull;

import java.nio.ByteBuffer;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-10
 * Time:   15:48
 * Life with Passion, Code with Creativity.
 */
public interface AudioConsumer {

   /**
     * @param data
     * @param offset
     * @param len
     * @param param
     */
    void write(@NonNull byte[] data, int offset, int len, @NonNull Bundle param);

    /**
     * @param data
     * @param param
     */
    void write(@NonNull ByteBuffer data, @NonNull Bundle param);

    void release();
}
