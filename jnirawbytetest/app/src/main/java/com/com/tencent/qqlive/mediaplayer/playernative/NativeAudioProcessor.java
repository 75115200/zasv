package com.com.tencent.qqlive.mediaplayer.playernative;


import io.github.landerlyoung.jenny.NativeMethodProxy;
import io.github.landerlyoung.jenny.NativeProxy;

/**
 * <pre>
 * Author: taylorcyang@tencent.com
 * Date:   2016-09-18
 * Time:   11:08
 * Life with Passion, Code with Creativity.
 * </pre>
 */
@NativeProxy(allMethods = false, allFields = false)
public class NativeAudioProcessor {
    private final Object mAudioProcessor;

    public NativeAudioProcessor(Object audioProcessor) {
        mAudioProcessor = audioProcessor;
    }

    private byte[] outData;
    private int outDataLen;

    @NativeMethodProxy
    public void processAudio(byte[] inPcmData,
                             int inPcmLen,
                             int sampleRate,
                             int channelCount,
                             long audioTimeStamp) {

    }

    @NativeMethodProxy
    private byte[] getOutData() {
        return outData;
    }

    @NativeMethodProxy
    private int getOutDataLen() {
        return outDataLen;
    }

    public int getSampleRate() {
        return 0;
    }

    public int getChannelCount() {
        return 0;
    }

    public long getAudioTimeStamp() {
        return 0;
    }

    public void writeData(byte[] data, int dataLen) {

    }
}
