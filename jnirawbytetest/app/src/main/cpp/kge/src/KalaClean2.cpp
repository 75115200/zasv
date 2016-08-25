#include "KalaClean2.h"
#include "CCleanNew3.h"


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
#define LOG_TAG "KalaClean2"

namespace KalaClean2 {

/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaClean2
 * Method:    private static long createClean2(int sampleRate, int channel)
 * Signature: (II)J
 */
jlong createClean2(JNIEnv *env, jclass clazz, jint sampleRate, jint channel) {
    CCleanNew3 *ins = new CCleanNew3();
    ins->Init(sampleRate, channel);
    return reinterpret_cast<jlong>(ins);
}


/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaClean2
 * Method:    private static int clean2Process(long handel, byte[] inBuffer, int size)
 * Signature: (J[BI)I
 */
jint clean2Process(JNIEnv *env, jclass clazz, jlong handel, jbyteArray inBuffer, jint size) {
    CCleanNew3 *ins = reinterpret_cast<CCleanNew3 *>(handel);
    jboolean isCopy;
    jbyte *buffer = env->GetByteArrayElements(inBuffer, &isCopy);

    jint ret = ins->Process(reinterpret_cast<char*>(buffer), size);

    LOGV("process size %d isCopy %s", size, isCopy == JNI_TRUE ? "true" : "false");

    env->ReleaseByteArrayElements(inBuffer, buffer, 0);

    return ret;
}


/*cd ..
 * Class:     com_young_jnirawbytetest_audiotest_KalaClean2
 * Method:    private void destroyClean2(long handel)
 * Signature: (J)V
 */
void destroyClean2(JNIEnv *env, jobject thiz, jlong handel) {
    CCleanNew3 *ins = reinterpret_cast<CCleanNew3 *>(handel);
    ins->Uninit();
    delete ins;
}


static const JNINativeMethod gsNativeMethods[] = {
        {
                /* method name      */ const_cast<char *>("createClean2"),
                /* method signature */ const_cast<char *>("(II)J"),
                /* function pointer */ reinterpret_cast<void *>(createClean2)
        },
        {
                /* method name      */ const_cast<char *>("clean2Process"),
                /* method signature */ const_cast<char *>("(J[BI)I"),
                /* function pointer */ reinterpret_cast<void *>(clean2Process)
        },
        {
                /* method name      */ const_cast<char *>("destroyClean2"),
                /* method signature */ const_cast<char *>("(J)V"),
                /* function pointer */ reinterpret_cast<void *>(destroyClean2)
        }
};
static const int gsMethodCount =
        sizeof(gsNativeMethods) / sizeof(JNINativeMethod);

/*
 * register Native functions
 */
void registerNativeFunctions(JNIEnv *env) {
    jclass clazz = env->FindClass("com/young/jnirawbytetest/audiotest/KalaClean2");
    env->RegisterNatives(clazz, gsNativeMethods, gsMethodCount);
}


} //endof namespace KalaClean2


