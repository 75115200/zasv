package com.young.droidpcmplayer;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    private Thread mPlayThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView text = (TextView) findViewById(R.id.text);
        text.setText(getIntent().toString());

        Uri data = getIntent().getData();

        Log.i(TAG, "onCreate: uri=" + data);

        if (data != null) {
            mPlayThread = new PlayThread(data, 44100, AudioFormat.CHANNEL_OUT_STEREO);
            mPlayThread.start();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (mPlayThread != null) {
            mPlayThread.interrupt();
        }
    }

    private class PlayThread extends Thread {

        private final Uri mUri;
        private final int mSampleRate;
        private final int mChannelConfig;

        public PlayThread(Uri uri, int sampleRate, int channelConfig) {
            mUri = uri;
            mSampleRate = sampleRate;
            mChannelConfig = channelConfig;
        }

        @Override
        public void run() {
            final int bufferSize = 2 *
                    AudioTrack.getMinBufferSize(mSampleRate, mChannelConfig,
                                                AudioFormat.ENCODING_PCM_16BIT);

            AudioTrack audioTrack = null;
            InputStream inputStream = null;

            try {
                inputStream = getContentResolver().openInputStream(mUri);
                if (inputStream == null) {
                    Log.e(TAG, "openInputStream failed" );
                    return;
                }
                audioTrack = new AudioTrack(
                        AudioManager.STREAM_MUSIC,
                        44100, AudioFormat.CHANNEL_OUT_STEREO, AudioFormat.ENCODING_PCM_16BIT,
                        bufferSize,
                        AudioTrack.MODE_STREAM
                );

                audioTrack.play();

                byte[] buffer = new byte[bufferSize];

                int read;
                while ((read = inputStream.read(buffer)) > 0 && !Thread.interrupted()) {
                    audioTrack.write(buffer, 0, read);
                }

            } catch (IOException e) {
                Log.e(TAG, "run: exception", e);
            } finally {
                if (audioTrack != null) {
                    audioTrack.release();
                }
                if (inputStream != null) {
                    try {
                        inputStream.close();
                    } catch (IOException ignore) {

                    }

                }
            }

            Log.i(TAG, "play finished");
        }
    }
}
