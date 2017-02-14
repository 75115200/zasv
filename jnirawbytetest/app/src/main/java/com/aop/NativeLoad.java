package com.aop;

import android.annotation.SuppressLint;
import android.util.Log;

import com.young.jnirawbytetest.MainActivity;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Pointcut;

import java.io.File;

/**
 * <pre>
 * Author: taylorcyang@tencent.com
 * Date:   2017-02-14
 * Time:   11:34
 * Life with Passion, Code with Creativity.
 * </pre>
 */
@Aspect
public class NativeLoad {
    private static final String TAG = "NativeLoad";

    @Pointcut("call(void java.lang.System.loadLibrary(String)) && !within(com.aop.NativeLoad)")
    private void pointSystemLoadLibarary() {
    }

    @Around("pointSystemLoadLibarary()")
    @SuppressLint("UnsafeDynamicallyLoadedCode")
    public void system_loadLibrary(ProceedingJoinPoint joinPoint) throws Throwable {
        Object[] args = joinPoint.getArgs();
        String libName = (String) args[0];

        Log.i(TAG, "system_loadLibrary: " + libName);

        try {
            System.loadLibrary(libName);
        } catch (UnsatisfiedLinkError notFound) {
            File libFile = findLibFile(libName);
            if (libFile.exists() && libFile.canRead()) {
                System.load(libFile.getAbsolutePath());
            } else {
                throw notFound;
            }
        }
    }

    private File findLibFile(String libName) {
        return new File(MainActivity.libPath + File.separator + System.mapLibraryName(libName));
    }
}
