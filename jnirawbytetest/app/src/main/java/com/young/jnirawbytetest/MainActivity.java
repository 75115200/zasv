package com.young.jnirawbytetest;

import android.os.Bundle;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.ViewAnimator;

import com.tencent.radio.ugc.record.widget.AudioTimeRulerView;
import com.young.jnirawbytetest.audiotest.KgeAudioTest;
import com.young.jnirawbytetest.audiotest.encoder.AACEncoderTestCase;

import java.util.Formatter;
import java.util.Locale;


public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    private ViewAnimator mViewAnimator;

    Thread mRunningThread;

    Handler h = new Handler();
    long totalTime = 10000;

    private void initRuler() {
        final AudioTimeRulerView rulerView = (AudioTimeRulerView) findViewById(R.id.time_ruler);
//        rulerView.setPointerDrawable(getResources().getDrawable(R.mipmap.line_radio));
        rulerView.setRulerColor(getResources().getColor(R.color.radio_time_ruler_line));
        rulerView.setTextColor(getResources().getColor(R.color.radio_time_ruler_text));

        rulerView.setTextSize(getResources().getDimension(R.dimen.radio_time_ruler_text));
        rulerView.setRulerTextPadding(getResources().getDimension(R.dimen.radio_time_ruler_text_padding));
        rulerView.setRulerSecondWidth(getResources().getDimension(R.dimen.radio_time_ruler_second_width));
        rulerView.setRulerHeight(getResources().getDimension(R.dimen.radio_time_ruler_height));
        rulerView.setRulerSecondaryHeight(getResources().getDimension(R.dimen.radio_time_ruler_secondary_height));
        rulerView.setRulerStrokeWidth(1);
        rulerView.setWaveColor(getResources().getColor(R.color.radio_time_ruler_line));

        rulerView.setRulerPrecision(4);
        rulerView.setWaveScalePrecision(20);
        rulerView.setMode(AudioTimeRulerView.MODE_FOLLOW_NEW_DATA);

        rulerView.setLayoutStrategy(new AudioTimeRulerView.LayoutStrategy() {
            @Override
            public void onViewSizeChanged(@NonNull AudioTimeRulerView view, int width, int height) {
                // display 6s
                view.setRulerSecondWidth(width / 6);
                view.setScrollXInitialOffset(-width / 2);
                view.setPointerPositionX(width / 2);
                view.setWaveStrokeWidth(width / 6 / view.getWaveScalePrecision() / 2);
            }
        });

        rulerView.setRulerAdapter(new AudioTimeRulerView.RulerAdapter() {
            StringBuilder sb = new StringBuilder();
            Formatter mFormatter = new Formatter(sb, Locale.US);
            @Override
            public CharSequence getTimeString(long timeSecond) {
                if (timeSecond < 0) {
                    return null;
                }
                int timeMin = (int) (timeSecond / 60);
                timeSecond %= 60;

                // avoid too much memory allocation
                sb.delete(0, sb.length());
                mFormatter.format("%02d:%02d", timeMin, (int) timeSecond);
                return sb;
            }

            @Override
            public long getTotalTime() {
                return totalTime;
            }

            @Override
            public int getDataForTime(long timeMillis) {
                if (timeMillis < 0) {
                    return 0;
                }
                int count = (int) (timeMillis / 50);
                return (int) ((count % 40) * (100f / 40));
            }
        });

        h.post(new Runnable() {
            @Override
            public void run() {
                totalTime += 50;
                rulerView.notifyDataAdded(totalTime - 50, 50);
                h.postDelayed(this, 50);
            }
        });

        rulerView.notifyDataSetChanged();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mViewAnimator = (ViewAnimator) findViewById(R.id.animator);

        initRuler();

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

        final Spinner reverbSpinner = ((Spinner) findViewById(R.id.reverb_spinner));
        reverbSpinner.setAdapter(new ArrayAdapter<>(
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
                reverbTest(10 + reverbSpinner.getSelectedItemPosition());
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

        findViewById(R.id.encode_m4a).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AACEncoderTestCase.testEncodeAndMuxerToM4A();
            }
        });

        findViewById(R.id.encode_aac).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AACEncoderTestCase.testEncodeAndMuxerToAAC();
            }
        });

        final Spinner superSoundSpinner = (Spinner) findViewById(R.id.super_sound_spinner);

        superSoundSpinner.setAdapter(new ArrayAdapter<>(
                MainActivity.this,
                android.R.layout.simple_list_item_1,
                new String[] {
                        "无音效",
                        "全景环绕",
                        "超重低音",
                        "清澈人声",
                        "现场律动",
                }
        ));

        findViewById(R.id.super_sound).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                superSoundTest(superSoundSpinner.getSelectedItemPosition());
            }
        });

        final Spinner voiceSpeedSpinner = (Spinner) findViewById(R.id.voice_speed_spinner);

        voiceSpeedSpinner.setAdapter(new ArrayAdapter<>(
                MainActivity.this,
                android.R.layout.simple_list_item_1,
                new String[] {
                        "0.5x",
                        "1.0x",
                        "1.5x",
                        "2.0x"
                }
        ));

        final Spinner channelSpinner = (Spinner) findViewById(R.id.channel_speed_spinner);
        channelSpinner.setAdapter(new ArrayAdapter<>(
                MainActivity.this,
                android.R.layout.simple_list_item_1,
                new String[] {
                        "1", "2"
                }
        ));

        findViewById(R.id.voice_speed).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int index = voiceSpeedSpinner.getSelectedItemPosition();
                int channel = channelSpinner.getSelectedItemPosition() + 1;
                switch (index) {
                    case 0:
                        voiceSpeedTest(channel, 0.5f);
                        break;
                    case 1: {
                        voiceSpeedTest(channel, 1.0f);
                        break;
                    }
                    case 2: {
                        voiceSpeedTest(channel, 1.5f);
                        break;
                    }
                    case 3: {
                        voiceSpeedTest(channel, 2f);
                        break;
                    }
                }
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

    private void superSoundTest(final int selectedItemPosition) {
        mRunningThread =
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            KgeAudioTest.superSound(selectedItemPosition);
                        } catch (Exception e) {
                            Log.e(TAG, "superSound: ", e);
                        }
                    }
                }, "superSound");
        mRunningThread.start();
    }

    private void voiceSpeedTest(final int channelCount, final float speedScale) {
        mRunningThread =
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            KgeAudioTest.voiceSpeed(channelCount, speedScale);
                        } catch (Exception e) {
                            Log.e(TAG, "superSound: ", e);
                        }
                    }
                }, "superSound");
        mRunningThread.start();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        super.onCreateOptionsMenu(menu);
        MenuItem item = menu.add("Switch");
        item.setShowAsAction(MenuItem.SHOW_AS_ACTION_ALWAYS);
        item.setIcon(getResources().getDrawable(android.R.drawable.ic_dialog_info));
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (super.onOptionsItemSelected(item)) {
            return true;
        } else if ("Switch".equals(item.getTitle())) {
            int current = mViewAnimator.getDisplayedChild();
            int count = mViewAnimator.getChildCount();
            mViewAnimator.setDisplayedChild((current + 1) % count);
            return true;
        }
        return false;
    }
}
