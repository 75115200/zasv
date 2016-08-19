package com.young.jnirawbytetest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.young.jnirawbytetest.audiotest.KgeAudioTest;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.clean2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                clean2Test();
            }
        });
    }

    public static void clean2Test() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    KgeAudioTest.testClean2();
                } catch (Exception e) {
                    Log.e(TAG, "runTestCase: ", e);
                }
            }
        }, "AudioTest").start();
    }
}
