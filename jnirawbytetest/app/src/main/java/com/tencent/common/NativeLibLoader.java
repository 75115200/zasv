package com.tencent.common;

import android.os.Build;
import android.support.annotation.NonNull;
import android.util.Log;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Array;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * <pre>
 * Author: taylorcyang@tencent.com
 * Date:   2017-02-14
 * Time:   14:22
 * Life with Passion, Code with Creativity.
 * </pre>
 * from tinker.
 */
public class NativeLibLoader {
    private static final String TAG = "Tinker.LoadLibrary";

    private NativeLibLoader() {

    }

    /**
     * link {@link #installNativeLibraryPath(ClassLoader, File)} but don't throws,
     * instead, return success or fail.
     */
    public static boolean installNativeLibraryPathSilently(@NonNull ClassLoader classLoader, @NonNull File folder) {
        try {
            installNativeLibraryPath(classLoader, folder);
            return true;
        } catch (Throwable throwable) {
            return false;
        }
    }

    public static void installNativeLibraryPath(@NonNull ClassLoader classLoader, @NonNull File folder)
            throws Throwable {
        if (folder == null || !folder.exists()) {
            Log.e(TAG, "installNativeLibraryPath, folder " + folder + " is illegal");
            return;
        }
        if (Build.VERSION.SDK_INT >= 23) {
            try {
                V23.install(classLoader, folder);
            } catch (Throwable throwable) {
                // install fail, try to treat it as v14
                Log.e(TAG, "installNativeLibraryPath, v23 fail, sdk: " + Build.VERSION.SDK_INT + ", error:", throwable);
                V14.install(classLoader, folder);
            }
        } else if (Build.VERSION.SDK_INT >= 14) {
            V14.install(classLoader, folder);
        } else {
            V4.install(classLoader, folder);
        }
    }

    private static final class V4 {
        private static void install(ClassLoader classLoader, File folder) throws Throwable {
            String addPath = folder.getPath();
            Field pathField = findField(classLoader, "libPath");
            StringBuilder libPath = new StringBuilder((String) pathField.get(classLoader));
            libPath.append(File.pathSeparator).append(addPath);
            pathField.set(classLoader, libPath.toString());

            Field libraryPathElementsFiled = findField(classLoader, "libraryPathElements");
            List<String> libraryPathElements = (List<String>) libraryPathElementsFiled.get(classLoader);
            libraryPathElements.add(0, addPath);
            libraryPathElementsFiled.set(classLoader, libraryPathElements);
        }
    }

    private static final class V14 {
        private static void install(ClassLoader classLoader, File folder) throws Throwable {
            Field pathListField = findField(classLoader, "pathList");
            Object dexPathList = pathListField.get(classLoader);

            expandFieldArray(dexPathList, "nativeLibraryDirectories", new File[]{folder});
        }
    }

    private static final class V23 {
        private static void install(ClassLoader classLoader, File folder) throws Throwable {
            Field pathListField = findField(classLoader, "pathList");
            Object dexPathList = pathListField.get(classLoader);

            Field nativeLibraryDirectories = findField(dexPathList, "nativeLibraryDirectories");

            List<File> libDirs = (List<File>) nativeLibraryDirectories.get(dexPathList);
            libDirs.add(0, folder);
            Field systemNativeLibraryDirectories =
                    findField(dexPathList, "systemNativeLibraryDirectories");
            List<File> systemLibDirs = (List<File>) systemNativeLibraryDirectories.get(dexPathList);
            Method makePathElements =
                    findMethod(dexPathList, "makePathElements", List.class, File.class, List.class);
            ArrayList<IOException> suppressedExceptions = new ArrayList<>();
            libDirs.addAll(systemLibDirs);
            Object[] elements = (Object[]) makePathElements.
                                                                   invoke(dexPathList, libDirs, null, suppressedExceptions);
            Field nativeLibraryPathElements = findField(dexPathList, "nativeLibraryPathElements");
            nativeLibraryPathElements.setAccessible(true);
            nativeLibraryPathElements.set(dexPathList, elements);
        }
    }

    public static Field findField(Object instance, String name) throws NoSuchFieldException {
        for (Class<?> clazz = instance.getClass(); clazz != null; clazz = clazz.getSuperclass()) {
            try {
                Field field = clazz.getDeclaredField(name);

                if (!field.isAccessible()) {
                    field.setAccessible(true);
                }

                return field;
            } catch (NoSuchFieldException e) {
                // ignore and search next
            }
        }

        throw new NoSuchFieldException("Field " + name + " not found in " + instance.getClass());
    }

    public static Field findField(Class<?> originClazz, String name) throws NoSuchFieldException {
        for (Class<?> clazz = originClazz; clazz != null; clazz = clazz.getSuperclass()) {
            try {
                Field field = clazz.getDeclaredField(name);

                if (!field.isAccessible()) {
                    field.setAccessible(true);
                }

                return field;
            } catch (NoSuchFieldException e) {
                // ignore and search next
            }
        }

        throw new NoSuchFieldException("Field " + name + " not found in " + originClazz);
    }

    private static Method findMethod(Object instance, String name, Class<?>... parameterTypes)
            throws NoSuchMethodException {
        for (Class<?> clazz = instance.getClass(); clazz != null; clazz = clazz.getSuperclass()) {
            try {
                Method method = clazz.getDeclaredMethod(name, parameterTypes);

                if (!method.isAccessible()) {
                    method.setAccessible(true);
                }

                return method;
            } catch (NoSuchMethodException e) {
                // ignore and search next
            }
        }

        throw new NoSuchMethodException("Method "
                + name
                + " with parameters "
                + Arrays.asList(parameterTypes)
                + " not found in " + instance.getClass());
    }

    private static void expandFieldArray(Object instance, String fieldName, Object[] extraElements)
            throws NoSuchFieldException, IllegalArgumentException, IllegalAccessException {
        Field jlrField = findField(instance, fieldName);

        Object[] original = (Object[]) jlrField.get(instance);
        Object[] combined = (Object[]) Array.newInstance(original.getClass().getComponentType(), original.length + extraElements.length);

        // NOTE: changed to copy extraElements first, for patch load first

        System.arraycopy(extraElements, 0, combined, 0, extraElements.length);
        System.arraycopy(original, 0, combined, extraElements.length, original.length);

        jlrField.set(instance, combined);
    }

}
