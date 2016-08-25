package com.young.jnirawbytetest.audiotest;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.EditText;

import com.young.jnirawbytetest.R;

import java.io.Closeable;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

/**
 * Created by wiizhang on 16/8/19.
 */
public class TestAudioEffectFragment extends Fragment {

    private static final String TAG = "TestAudioEffectFragment";

    private AudioTrack mTrack;

    private int mOutputBufferSize;
    private int mSampleRate = 44100;
    private int mChannelCount = 2;
    private String filePath;

    private long mReverbPtr, mVoiceShiftPtr, mVolumeScalarPtr, mAutoGainPtr, mGetVolumePtr;

    private EditText mParamEdit, mParamEdit2, mParamEdit3;
    private CheckBox mEnableGain;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        filePath = PCM.STEREO;
        mSampleRate = 44100;
        mChannelCount = 2;
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater,
                             @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        KgeAudioTest.loadLib();

        View v = inflater.inflate(R.layout.audio_effect, container, false);

        mParamEdit = (EditText) v.findViewById(R.id.param_input);
        mParamEdit2 = (EditText) v.findViewById(R.id.param_input2);
        mParamEdit3 = (EditText) v.findViewById(R.id.param_input3);
        mEnableGain = (CheckBox) v.findViewById(R.id.gain);

        v.findViewById(R.id.process_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mChannelCount = 1;
                processPCMFile(filePath);
            }
        });

        doInit();

        return v;
    }

    private void doInit() {
        int channelFormat = mChannelCount == 1
                ? AudioFormat.CHANNEL_OUT_MONO
                : AudioFormat.CHANNEL_OUT_STEREO;
        mOutputBufferSize = AudioTrack.getMinBufferSize(
                mSampleRate,
                channelFormat,
                AudioFormat.ENCODING_PCM_16BIT) * 2;

        mOutputBufferSize = 384 * 2;

        mTrack = new AudioTrack(AudioManager.STREAM_MUSIC,
                                mSampleRate,
                                channelFormat,
                                AudioFormat.ENCODING_PCM_16BIT,
                                mOutputBufferSize,
                                AudioTrack.MODE_STREAM);

        mReverbPtr = createReverb4(mSampleRate, mChannelCount);
        mVoiceShiftPtr = createVoiceShift(mSampleRate, mChannelCount);
        mVolumeScalarPtr = createVolumeScalar(mSampleRate, mChannelCount);
        mGetVolumePtr = createGetVolume();
        mAutoGainPtr = createAutoGain(mSampleRate, mChannelCount);
    }

    private void processPCMFile(final String path) {
        final int input1 = getEditTextInput(mParamEdit);
        final int input2 = getEditTextInput(mParamEdit2);
        final int input3 = getEditTextInput(mParamEdit3);
        final boolean enableGain = mEnableGain.isChecked();
        new AsyncTask<Void, Void, Void>() {
            @Override
            protected Void doInBackground(Void... params) {
                File f = new File(path);
                FileInputStream fis = null;

                byte[] bufferA = new byte[mOutputBufferSize];
                byte[] bufferB = new byte[mOutputBufferSize];
                try {
                    fis = new FileInputStream(f);
                    int readCount = 0;
                    mTrack.play();
                    while ((readCount = fis.read(bufferA)) > 0) {
                        int result = getVolume(mGetVolumePtr, bufferA, readCount);
                        Log.d(TAG, "volume is " + result);

                        doVolumeScalar(mVolumeScalarPtr, input3, bufferA, readCount);
                        if (enableGain) {
                            doAutoGain(mAutoGainPtr, bufferA, readCount);
                        }
                        doReverb4(mReverbPtr, input1, bufferA, readCount, bufferB, readCount);
                        doVoiceShift(mVoiceShiftPtr, input2, bufferB, readCount, bufferA, readCount);
                        mTrack.write(bufferA, 0, readCount);
                    }
                } catch (IOException e) {
                    Log.e(TAG, "processPCMFile() fail", e);
                } finally {
                    closeSilent(fis);
                }

                return null;
            }
        }.execute();
    }

    private static int getEditTextInput(EditText editText) {
        int result = 0;
        try {
            result = Integer.valueOf(editText.getText().toString());
        } catch (NumberFormatException e) {

        }
        return result;
    }

    private static void closeSilent(Closeable c) {
        if (c != null) {
            try {
                c.close();
            } catch (IOException e) {
                //omit
            }
        }
    }

    @Override
    public void onDestroy() {
        Log.d(TAG, "onDestroy() and perform release");
        super.onDestroy();
        if (mTrack != null) {
            mTrack.release();
        }
        releaseReverb4(mReverbPtr);
        releaseVoiceShift(mVoiceShiftPtr);
        releaseVolumeScalar(mVolumeScalarPtr);
        releaseGetVolume(mGetVolumePtr);
        releaseAutoGain(mAutoGainPtr);
    }

    public native long createGetVolume();

    public native void releaseGetVolume(long handle);

    public native int getVolume(long handle, byte[] dataIn, int sizeIn);

    public native long createAutoGain(int sampleRate, int channel);

    public native void releaseAutoGain(long handle);

    public native int doAutoGain(long handle, byte[] bufferIn, int size);

    public native long createReverb4(int sampleRate, int channel);

    public native void releaseReverb4(long handle);

    public native int doReverb4(long handle, int typeID, byte[] dataIn, int sizeIn, byte[] dataOut, int sizeOut);

    public native long createVoiceShift(int sampleRate, int channel);

    public native void releaseVoiceShift(long handle);

    public native int doVoiceShift(long handle, int typeID, byte[] dataIn, int sizeIn, byte[] dataOut, int sizeOut);

    public native long createVolumeScalar(int sampleRate, int channel);

    public native void releaseVolumeScalar(long handle);

    public native int doVolumeScalar(long handle, int factor, byte[] dataIn, int sizeIn);

}
