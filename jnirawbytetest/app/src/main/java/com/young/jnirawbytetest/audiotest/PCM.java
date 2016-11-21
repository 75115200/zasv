package com.young.jnirawbytetest.audiotest;

import android.os.Environment;

/**
 * Author: landerlyoung@gmail.com
 * Date:   2016-08-25
 * Time:   20:17
 * Life with Passion, Code with Creativity.
 */
public class PCM {
    private static final String path =
            Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS)
                       .getAbsolutePath();

    public static final String MONO = path + "/mono.pcm";
    public static final String MONO2 = path + "/pp.mono.pcm.raw";
    public static final String MONO_MUSIC = path + "/bgm.mono.pcm";
    public static final String STEREO = path + "/haha.stereo.pcm";
    public static final String STEREO_MUSIC = path + "/bgm.stereo.pcm";
}
