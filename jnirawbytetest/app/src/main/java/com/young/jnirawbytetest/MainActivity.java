package com.young.jnirawbytetest;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;

import com.young.jnirawbytetest.audiotest.KgeAudioTest;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    Thread mRunningThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.stop).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (mRunningThread != null) {
                    mRunningThread.interrupt();
                }
            }
        });

        findViewById(R.id.clean2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                clean2Test();
            }
        });

        findViewById(R.id.mix).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
               mixTest();
            }
        });

        final EditText toneVal = (EditText) findViewById(R.id.tone_val);

        findViewById(R.id.tone).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int t = 0;
                try {
                    t = Integer.parseInt(toneVal.getText().toString());
                } catch (NumberFormatException e) {
                    //fuck
                }
                toneTest(t);
            }
        });

        final Spinner s = (Spinner) findViewById(R.id.shift_spinner);
        s.setAdapter(new ArrayAdapter<>(
                MainActivity.this,
                android.R.layout.simple_list_item_1,
                new String[] {
                        "EFFECT",
                        "SOPRANO",
                        "BASSO",
                        "BABY",
                        "AUTOTUNE",
                        "METAL",
                        "CHORUS"
                }));
        findViewById(R.id.voice_shift).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                voiceShiftTest(s.getSelectedItemPosition());
            }
        });

        ((Spinner) findViewById(R.id.reverb_spinner))
                .setAdapter(new ArrayAdapter<>(
                        MainActivity.this,
                        android.R.layout.simple_list_item_1,
                        new String[] {
                                "NO_EFFECT",
                                "KTV",
                                "温暖",
                                "磁性",
                                "空灵",
                                "悠远",
                                "迷幻",
                                "老唱片",
                                "无用×",
                        }));

        findViewById(R.id.reverb).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                reverbTest(10 + s.getSelectedItemPosition());
            }
        });

        final EditText scaleValue = (EditText) findViewById(R.id.scale_val);
        findViewById(R.id.volume_scalar).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int t = 0;
                try {
                    t = Integer.parseInt(scaleValue.getText().toString());
                } catch (NumberFormatException e) {
                    //fuck
                }
                volumeScaleTest(t);
            }
        });

        findViewById(R.id.gain).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                gain();
            }
        });
    }

    public void clean2Test() {
        mRunningThread =
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    KgeAudioTest.testClean2();
                } catch (Exception e) {
                    Log.e(TAG, "clean2Test: ", e);
                }
            }
        }, "AudioTest");
        mRunningThread.start();
    }


    public void toneTest(final int toneVal) {
        mRunningThread =
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            KgeAudioTest.testTone(toneVal);
                        } catch (Exception e) {
                            Log.e(TAG, "tone: ", e);
                        }
                    }
                }, "ToneTest");
        mRunningThread.start();
    }

    public void mixTest() {
        mRunningThread =
         new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    KgeAudioTest.mixTest(false);
                } catch (Exception e) {
                    Log.e(TAG, "mixTest: ", e);
                }
            }
        }, "AudioTest");
        mRunningThread.start();
    }

    public void voiceShiftTest(final int typeId) {
        mRunningThread =
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    KgeAudioTest.voiceShiftTest(typeId);
                } catch (Exception e) {
                    Log.e(TAG, "mixTest: ", e);
                }
            }
        }, "VoiceShift");
        mRunningThread.start();
    }

    public void reverbTest(final int typeId) {
        mRunningThread =
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            KgeAudioTest.reverbTest(typeId);
                        } catch (Exception e) {
                            Log.e(TAG, "mixTest: ", e);
                        }
                    }
                }, "ReverbTest");
        mRunningThread.start();
    }

    public void volumeScaleTest(final int scale) {
        mRunningThread =
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            KgeAudioTest.volumeScaleTest(scale);
                        } catch (Exception e) {
                            Log.e(TAG, "scale: ", e);
                        }
                    }
                }, "ScaleTest");
        mRunningThread.start();
    }
    public void gain() {
        mRunningThread =
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    KgeAudioTest.testGain();
                } catch (Exception e) {
                    Log.e(TAG, "mixTest: ", e);
                }
            }
        }, "VoiceShift");
        mRunningThread.start();
    }
}
