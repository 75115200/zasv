#include "KalaToneShift.h"
#include "CToneShift.h"

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
#define LOG_TAG "KalaToneShift"

namespace KalaToneShift {

/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaToneShift
 * Method:    private static long nativeCreate(int sampleRate, int channelCount)
 * Signature: (II)J
 */
jlong nativeCreate(JNIEnv *env, jclass clazz, jint sampleRate, jint channelCount) {
    CToneShift *ins = new CToneShift();
    ins->Init(sampleRate, channelCount);
    return reinterpret_cast<jlong>(ins);
}


/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaToneShift
 * Method:    private static int setShiftValue(long handle, int shiftVal)
 * Signature: (JI)I
 */
jint setShiftValue(JNIEnv *env, jclass clazz, jlong handle, jint shiftVal) {
    CToneShift *ins = reinterpret_cast<CToneShift *>(handle);
    LOGV("%s %d", __FUNCTION__, shiftVal);
    return ins->SetShiftValue(shiftVal);
}

/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaToneShift
 * Method:    private static int process(long handel, byte[] inBuf, int inSize, byte[] outBuf, int outSize)
 * Signature: (J[BI[BI)I
 */
jint process(JNIEnv *env, jclass clazz, jlong handel, jbyteArray inBuf, jint inSize,
             jbyteArray outBuf, jint outSize) {
    CToneShift *ins = reinterpret_cast<CToneShift *>(handel);
    if (ins) {
        LOGV("p in %d  out %d", inSize, outSize);
        jbyte *in = env->GetByteArrayElements(inBuf, nullptr);
        jbyte *out = env->GetByteArrayElements(outBuf, nullptr);
        jint ret = ins->Process(
                reinterpret_cast<char *>(in), inSize,
                reinterpret_cast<char *>(out), outSize);

        env->ReleaseByteArrayElements(inBuf, in, JNI_ABORT);
        env->ReleaseByteArrayElements(outBuf, out, 0);
        return ret;
    }
    return 0;
}


/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaToneShift
 * Method:    private static void release(long handel)
 * Signature: (J)V
 */
void release(JNIEnv *env, jclass clazz, jlong handel) {
    CToneShift *ins = reinterpret_cast<CToneShift *>(handel);
    if (ins) {
        ins->Uninit();
    }
    delete ins;
}


static const JNINativeMethod gsNativeMethods[] = {
        {
                /* method name      */ const_cast<char *>("nativeCreate"),
                /* method signature */ const_cast<char *>("(II)J"),
                /* function pointer */ reinterpret_cast<void *>(nativeCreate)
        },
        {
                /* method name      */ const_cast<char *>("setShiftValue"),
                /* method signature */ const_cast<char *>("(JI)I"),
                /* function pointer */ reinterpret_cast<void *>(setShiftValue)
        },
        {
                /* method name      */ const_cast<char *>("process"),
                /* method signature */ const_cast<char *>("(J[BI[BI)I"),
                /* function pointer */ reinterpret_cast<void *>(process)
        },
        {
                /* method name      */ const_cast<char *>("release"),
                /* method signature */ const_cast<char *>("(J)V"),
                /* function pointer */ reinterpret_cast<void *>(release)
        }
};
static const int gsMethodCount =
        sizeof(gsNativeMethods) / sizeof(JNINativeMethod);

/**
 * register Native functions
 * @returns success or not
 */
bool registerNativeFunctions(JNIEnv *env) {
        LOGI("KalaToneShift registerNativeFunction");
    jclass clazz = env->FindClass(FULL_CLASS_NAME);
    return clazz != nullptr
           && 0 == env->RegisterNatives(clazz, gsNativeMethods, gsMethodCount);
}


} //endof namespace KalaToneShift

