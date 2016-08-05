package com.young.jnirawbytetest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.text).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                performanceTest();
            }
        });

    }

    public static void performanceTest() {
        final int limit = 1024*1024;
        for (int i = 0; i < limit; i++) {
            JavaJniPerformanceCompare.passByteArrayToNative(null);
        }
    }
}
