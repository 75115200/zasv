#include "JavaJniPerformanceCompare.h"
#include <cstring>

#ifdef DEBUG

#include <android/log.h>

#define LOGV(...)   __android_log_print((int)ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...)   __android_log_print((int)ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)   __android_log_print((int)ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...)   __android_log_print((int)ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...)   __android_log_print((int)ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#else
#define LOGV(...)
#define LOGD(...)
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#endif



//change to whatever you like
#define LOG_TAG "JavaJniPerformanceCompare"

namespace JavaJniPerformanceCompare {

/*
 * Class:     com_young_jnirawbytetest_JavaJniPerformanceCompare
 * Method:    public static int add(int a, int b)
 * Signature: (II)I
 */
jint add(JNIEnv *env, jclass clazz, jint a, jint b) {
    return a + b;
}


/*
 * Class:     com_young_jnirawbytetest_JavaJniPerformanceCompare
 * Method:    public static int batchAdd(int a, int b, int count)
 * Signature: (III)I
 */
jint batchAdd(JNIEnv *env, jclass clazz, jint a, jint b, jint count) {
    jint c = 0;
    for (jint i = 0; i < count; ++i) {
        c += a + b;
    }
    return c;
}


/*
 * Class:     com_young_jnirawbytetest_JavaJniPerformanceCompare
 * Method:    public static void passByteArrayToNative(byte[] data)
 * Signature: ([B)V
 */
void passByteArrayToNative(JNIEnv *env, jclass clazz, jbyteArray data) {
    jboolean isCopy;
    const jint length = env->GetArrayLength(data);
    jbyte *arr = env->GetByteArrayElements(data, &isCopy);
    std::memset(arr, 1, length);
    env->ReleaseByteArrayElements(data, arr, 0);
    LOGV("GetByteArrayElements isCopy %s", (isCopy ? "true" : "false"));
}


/*
 * Class:     com_young_jnirawbytetest_JavaJniPerformanceCompare
 * Method:    public static void passByteBufferToNative(java.nio.ByteBuffer data)
 * Signature: (Ljava/nio/ByteBuffer;)V
 */
void passByteBufferToNative(JNIEnv *env, jclass clazz, jobject data) {
    jbyte *arr = static_cast<jbyte *>(env->GetDirectBufferAddress(data));
    jlong length = env->GetDirectBufferCapacity(data);
    std::memset(arr, 1, length);
}


/*
 * Class:     com_young_jnirawbytetest_JavaJniPerformanceCompare
 * Method:    public static void cppBatchMemcpy(int size, int count)
 * Signature: (II)V
 */
void cppBatchMemcpy(JNIEnv *env, jclass clazz, jint size, jint count) {
    char *src = new char[size];
    char *dst = new char[size];
    for (int i = 0; i < count; i++) {
        std::memcpy(dst, src, size);
    }
    delete[] src;
    delete[] dst;
}


/*
 * Class:     com_young_jnirawbytetest_JavaJniPerformanceCompare
 * Method:    public static void cppBatchMemset(int size, int count)
 * Signature: (II)V
 */
void cppBatchMemset(JNIEnv *env, jclass clazz, jint size, jint count) {
    char *data = new char[size];
    for (int i = 0; i < count; i++) {
        std::memset(data, 1, size);
    }
    delete[] data;
}


static const JNINativeMethod gsNativeMethods[] = {
        {
                /* method name      */ const_cast<char *>("add"),
                /* method signature */ const_cast<char *>("(II)I"),
                /* function pointer */ reinterpret_cast<void *>(add)
        },
        {
                /* method name      */ const_cast<char *>("batchAdd"),
                /* method signature */ const_cast<char *>("(III)I"),
                /* function pointer */ reinterpret_cast<void *>(batchAdd)
        },
        {
                /* method name      */ const_cast<char *>("passByteArrayToNative"),
                /* method signature */ const_cast<char *>("([B)V"),
                /* function pointer */ reinterpret_cast<void *>(passByteArrayToNative)
        },
        {
                /* method name      */ const_cast<char *>("passByteBufferToNative"),
                /* method signature */ const_cast<char *>("(Ljava/nio/ByteBuffer;)V"),
                /* function pointer */ reinterpret_cast<void *>(passByteBufferToNative)
        },
        {
                /* method name      */ const_cast<char *>("cppBatchMemcpy"),
                /* method signature */ const_cast<char *>("(II)V"),
                /* function pointer */ reinterpret_cast<void *>(cppBatchMemcpy)
        },
        {
                /* method name      */ const_cast<char *>("cppBatchMemset"),
                /* method signature */ const_cast<char *>("(II)V"),
                /* function pointer */ reinterpret_cast<void *>(cppBatchMemset)
        }
};
static const int gsMethodCount =
        sizeof(gsNativeMethods) / sizeof(JNINativeMethod);

/*
 * register Native functions
 */
void registerNativeFunctions(JNIEnv *env) {
    jclass clazz = env->FindClass("com/young/jnirawbytetest/JavaJniPerformanceCompare");
    env->RegisterNatives(clazz, gsNativeMethods, gsMethodCount);
}


} //endof namespace JavaJniPerformanceCompare


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env),
                   JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    JavaJniPerformanceCompare::registerNativeFunctions(env);
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {

}
