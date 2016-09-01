package com.young.jnirawbytetest.audiotest.logic;

import android.media.AudioFormat;
import android.os.Parcel;
import android.os.Parcelable;

import java.nio.ByteOrder;

/**
 * Author: taylorcyang@tencent.com
 * Date:   2016-08-09
 * Time:   19:38
 * Life with Passion, Code with Creativity.
 */
public final class PCMFormat implements Parcelable {
    /**
     * usually 44100
     */
    public int sampleRate;

    /**
     * @see android.media.AudioFormat#ENCODING_PCM_16BIT
     */
    public int audioFormat;

    /**
     * byte order
     *
     * @see ByteOrder#LITTLE_ENDIAN
     * @see ByteOrder#BIG_ENDIAN
     */
    public ByteOrder endian = ByteOrder.LITTLE_ENDIAN;

    /**
     * @see android.media.AudioFormat#CHANNEL_IN_MONO
     * @see android.media.AudioFormat#CHANNEL_OUT_STEREO
     */
    public int outChannelConfig;

    /**
     * @see android.media.AudioFormat#CHANNEL_IN_MONO
     */
    public int inChannelConfig;

    public int bitRate;

    public int bufferSize;

    public int getInChannelCount() {
        if (inChannelConfig == AudioFormat.CHANNEL_IN_MONO) {
            return 1;
        } else {
            return 2;
        }
    }

    public int getOutChannelCount() {
        if (outChannelConfig == AudioFormat.CHANNEL_OUT_MONO) {
            return 1;
        } else {
            return 2;
        }
    }


    @Override
    public String toString() {
        return "PCMFormat{" +
                "sampleRate=" + sampleRate +
                ", audioFormat=" + audioFormat +
                ", endian=" + endian +
                ", outChannelConfig=" + outChannelConfig +
                ", inChannelConfig=" + inChannelConfig +
                ", bufferSize=" + bufferSize +
                '}';
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeInt(this.sampleRate);
        dest.writeInt(this.audioFormat);
        dest.writeByte(this.endian == ByteOrder.LITTLE_ENDIAN ? (byte) 0 : (byte) 1);
        dest.writeInt(this.outChannelConfig);
        dest.writeInt(this.inChannelConfig);
        dest.writeInt(this.bufferSize);
    }

    public PCMFormat() {
    }

    protected PCMFormat(Parcel in) {
        this.sampleRate = in.readInt();
        this.audioFormat = in.readInt();
        this.endian = in.readByte() == 0 ? ByteOrder.LITTLE_ENDIAN : ByteOrder.BIG_ENDIAN;
        this.outChannelConfig = in.readInt();
        this.inChannelConfig = in.readInt();
        this.bufferSize = in.readInt();
    }

    public static final Creator<PCMFormat> CREATOR = new Creator<PCMFormat>() {
        @Override
        public PCMFormat createFromParcel(Parcel source) {
            return new PCMFormat(source);
        }

        @Override
        public PCMFormat[] newArray(int size) {
            return new PCMFormat[size];
        }
    };
}
