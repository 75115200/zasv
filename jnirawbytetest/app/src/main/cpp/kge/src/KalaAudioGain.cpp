#include "KalaAudioGain.h"
#include <CautoGain.h>

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
#define LOG_TAG "KalaAudioGain"

namespace KalaAudioGain {

/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaAudioGain
 * Method:    private static long create(int sampleRate, int dualChannel)
 * Signature: (II)J
 */
jlong create(JNIEnv *env, jclass clazz, jint sampleRate, jint channelCount) {
    CautoGain *ins = new CautoGain();
    ins->Init(sampleRate, channelCount);

    return reinterpret_cast<jlong>(ins);
}

/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaAudioGain
 * Method:    private static int process(long nativeHandel, byte[] inOutBuffer, int size)
 * Signature: (J[BI)I
 */
jint process(JNIEnv *env, jclass clazz, jlong nativeHandel, jbyteArray inOutBuffer, jint size) {
    CautoGain *ins = reinterpret_cast<CautoGain*>(nativeHandel);
    jbyte *bytes = env->GetByteArrayElements(inOutBuffer, nullptr);

    jint ret = ins->Process(reinterpret_cast<char *>(bytes), size);

    env->ReleaseByteArrayElements(inOutBuffer, bytes, 0);

    return ret;
}


/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaAudioGain
 * Method:    private static void release(long nativeHandel)
 * Signature: (J)V
 */
void release(JNIEnv *env, jclass clazz, jlong nativeHandel) {
    CautoGain *ins = reinterpret_cast<CautoGain*>(nativeHandel);
    ins->Uninit();
    delete ins;
}


static const JNINativeMethod gsNativeMethods[] = {
    {
        /* method name      */ const_cast<char *>("create"),
        /* method signature */ const_cast<char *>("(II)J"),
        /* function pointer */ reinterpret_cast<void *>(create)
    },    {
        /* method name      */ const_cast<char *>("process"),
        /* method signature */ const_cast<char *>("(J[BI)I"),
        /* function pointer */ reinterpret_cast<void *>(process)
    },    {
        /* method name      */ const_cast<char *>("release"),
        /* method signature */ const_cast<char *>("(J)V"),
        /* function pointer */ reinterpret_cast<void *>(release)
    }
};
static const int gsMethodCount =
    sizeof(gsNativeMethods) / sizeof(JNINativeMethod);

/*
 * register Native functions
 */
void registerNativeFunctions(JNIEnv *env) {
    jclass clazz = env->FindClass("com/young/jnirawbytetest/audiotest/KalaAudioGain");
    env->RegisterNatives(clazz, gsNativeMethods, gsMethodCount);
}



} //endof namespace KalaAudioGain

