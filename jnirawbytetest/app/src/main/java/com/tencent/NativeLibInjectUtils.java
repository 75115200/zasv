package com.tencent;

import android.content.Context;
import android.util.Log;

import java.io.File;
import java.lang.reflect.Array;
import java.lang.reflect.Field;

import dalvik.system.PathClassLoader;

/**
 * <pre>
 * Author: taylorcyang@tencent.com
 * Date:   2017-02-13
 * Time:   20:30
 * Life with Passion, Code with Creativity.
 * </pre>
 * Android change the way BaseDexLoader find native library constantly.
 * Using reflection is quite annoying to deal with platform differences.
 */
public class NativeLibInjectUtils {
    private static final String TAG = "NativeLibInjectUtils";

    private final static String CLASS_LOADER_BASE_DEX = "dalvik.system.BaseDexClassLoader";
    public static final String LIB_DIR_FILED_NAME = "nativeLibraryDirectories";


    /**
     * 把自定义的lib文件夹添加到PathClassLoader的搜索路径中
     *
     * @param context Context
     * @param libPath 自定义的lib文件夹路径
     *
     * @return 是否成功
     */
    public static boolean addLibPath(Context context, String libPath) {
        Log.d(TAG, "addLibPath: " + libPath);
        PathClassLoader pathClassLoader = (PathClassLoader) context.getClassLoader();

        try {
            Object pathList = getPathList(pathClassLoader);
            Object libDirs = appendArray(getNativeLibraryDirectories(pathList),
                    new File(libPath),
                    true);
            setField(pathList, pathList.getClass(), LIB_DIR_FILED_NAME, libDirs);
        } catch (Exception e) {
            Log.e(TAG, "addLibPath fail! ", e);
            return false;
        }

        return true;
    }

    private static Object getPathList(Object baseDexClassLoader) throws IllegalArgumentException, NoSuchFieldException,
            IllegalAccessException, ClassNotFoundException {
        return getField(baseDexClassLoader, Class.forName(CLASS_LOADER_BASE_DEX), "pathList");
    }

    private static Object getNativeLibraryDirectories(Object paramObject) throws IllegalArgumentException, NoSuchFieldException,
            IllegalAccessException {
        return getField(paramObject, paramObject.getClass(), LIB_DIR_FILED_NAME);
    }

    private static Object getField(Object obj, Class<?> cl, String field) throws NoSuchFieldException,
            IllegalArgumentException, IllegalAccessException {
        Field localField = cl.getDeclaredField(field);
        localField.setAccessible(true);
        return localField.get(obj);
    }

    private static void setField(Object obj, Class<?> cl, String field, Object value) throws NoSuchFieldException,
            IllegalArgumentException, IllegalAccessException {
        Field localField = cl.getDeclaredField(field);
        localField.setAccessible(true);
        localField.set(obj, value);
    }

    private static Object appendArray(Object array, Object value, boolean insertAtFirst) {
        Class<?> localClass = array.getClass().getComponentType();
        int i = Array.getLength(array);
        int j = i + 1;
        Object localObject = Array.newInstance(localClass, j);
        if (insertAtFirst) {
            Array.set(localObject, 0, value);
            for (int k = 1; k < j; ++k) {
                Array.set(localObject, k, Array.get(array, k - 1));
            }
        } else {
            for (int k = 0; k < j; ++k) {
                if (k < i) {
                    Array.set(localObject, k, Array.get(array, k));
                } else {
                    Array.set(localObject, k, value);
                }
            }
        }
        return localObject;
    }
}
