package com.young.jnirawbytetest.audiotest.logic;

import android.os.Bundle;
import android.support.annotation.NonNull;

import java.nio.ByteBuffer;

/**
 * Author: landerlyoung@gmail.com
 * Date:   2016-08-10
 * Time:   16:42
 * Life with Passion, Code with Creativity.
 */
public interface AudioProcessor {

    void process(@NonNull byte[] inOutData, int offset, int len, @NonNull Bundle param);

    void process(@NonNull ByteBuffer inOutData, @NonNull Bundle param);

}
