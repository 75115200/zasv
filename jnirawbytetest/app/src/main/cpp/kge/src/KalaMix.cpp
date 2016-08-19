#include "KalaMix.h"
#include "CMixSound.h"

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
#define LOG_TAG "KalaMix"

namespace KalaMix {

/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaMix
 * Method:    private static long create(int sampleRate, int channel)
 * Signature: (II)J
 */
jlong create(JNIEnv *env, jclass clazz, jint sampleRate, jint channel) {
    CMixSound *ins = new CMixSound();
    ins->Init(sampleRate, channel);
    return reinterpret_cast<jlong>(ins);
}


/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaMix
 * Method:    private static int process(long handel, byte[] bgm, int bgmSize, byte[] vocal, int vocalSize, byte[] out, int outSize)
 * Signature: (J[BI[BI[BI)I
 */
jint process(JNIEnv *env, jclass clazz,
             jlong handel,
             jbyteArray bgm, jint bgmSize,
             jbyteArray vocal, jint vocalSize,
             jbyteArray out, jint outSize) {

    CMixSound *ins = reinterpret_cast<CMixSound *>(handel);

    jboolean isBgmCopy;
    jbyte *bgmBytes = env->GetByteArrayElements(bgm, &isBgmCopy);
    char *bgmBuf = reinterpret_cast<char *>(bgmBytes);


    jboolean isVocalCopy;
    jbyte *vocalBytes = env->GetByteArrayElements(vocal, &isVocalCopy);
    char *vocalBuf = reinterpret_cast<char *>(vocalBytes);

    jboolean isOutCopy;
    jbyte *outBytes = env->GetByteArrayElements(out, &isOutCopy);

    char *outBuf = reinterpret_cast<char *>(outBytes);

    jint ret = ins->Process(
            bgmBuf, bgmSize,
            vocalBuf, vocalSize,
            outBuf, outSize
    );

    env->ReleaseByteArrayElements(bgm, bgmBytes, 0);
    env->ReleaseByteArrayElements(vocal, vocalBytes, 0);
    env->ReleaseByteArrayElements(out, outBytes, 0);
    return ret;
}


/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaMix
 * Method:    private void release(long handel)
 * Signature: (J)V
 */
void release(JNIEnv *env, jobject thiz, jlong handel) {
    CMixSound *ins = reinterpret_cast<CMixSound *>(handel);
    ins->Uninit();
    delete ins;
    return;
}


static const JNINativeMethod gsNativeMethods[] = {
        {
                /* method name      */ const_cast<char *>("create"),
                /* method signature */ const_cast<char *>("(II)J"),
                /* function pointer */ reinterpret_cast<void *>(create)
        },
        {
                /* method name      */ const_cast<char *>("process"),
                /* method signature */ const_cast<char *>("(J[BI[BI[BI)I"),
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

/*
 * register Native functions
 */
void registerNativeFunctions(JNIEnv *env) {
    jclass clazz = env->FindClass("com/young/jnirawbytetest/audiotest/KalaMix");
    env->RegisterNatives(clazz, gsNativeMethods, gsMethodCount);
}


} //endof namespace KalaMix
