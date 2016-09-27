package com.young.jnirawbytetest.audiotest.logic;

import android.os.Bundle;
import android.support.annotation.NonNull;

import java.io.BufferedOutputStream;
import java.io.Closeable;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;

/**
 * Author: landerlyoung@gmail.com
 * Date:   2016-08-10
 * Time:   17:27
 * Life with Passion, Code with Creativity.
 */
public class SaveToFilePcmConsumer implements AudioConsumer {

    private FileChannel mFileChannel;
    private OutputStream mFileOutputStream;

    private final String mFilePath;


    public SaveToFilePcmConsumer(String path) {
        mFilePath = path;
    }

    @Override
    public void write(@NonNull byte[] data, int offset, int len, @NonNull Bundle param) {
        try {
            if (mFileOutputStream == null) {
                mFileOutputStream = new BufferedOutputStream(new FileOutputStream(mFilePath));
            }
            mFileOutputStream.write(data, offset, len);
        } catch (IOException e) {
            param.putBoolean("success?", false);
        }
    }

    @Override
    public void write(@NonNull ByteBuffer data, @NonNull Bundle param) {
        try {
            if (mFileChannel == null) {
                mFileChannel = new FileInputStream(mFilePath).getChannel();
            }
            mFileChannel.write(data, 0);
        } catch (IOException e) {
            param.putBoolean("success?", false);
        }
    }

    @Override
    public void release() {
        closeSilently(mFileChannel);
        closeSilently(mFileOutputStream);
    }

    private void closeSilently(Closeable fileOutputStream) {
        try {
            fileOutputStream.close();
        } catch (IOException e) {

        }
    }


}
