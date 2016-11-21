#include "KalaVoiceShift.h"
#include "CVoiceShift.h"

#if (defined(DEBUG) && defined(ANDROID))

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
#define LOG_TAG "KalaVoiceShift"

#define jbool2str(val) (val == JNI_TRUE ? "true" : "false")

namespace KalaVoiceShift {

/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaVoiceShift
 * Method:    private static long create(int sampleRate, int channel)
 * Signature: (II)J
 */
jlong create(JNIEnv *env, jclass clazz, jint sampleRate, jint channel) {
    CVoiceShift *ins = new CVoiceShift();
    ins->Init(sampleRate, channel, nullptr, 0);

    return reinterpret_cast<jlong>(ins);
}


/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaVoiceShift
 * Method:    private static int process(long nativeHandel, byte[] inBuffer, int inSize, byte[] outBuffer, int outBufferSize)
 * Signature: (J[BI[BI)I
 */
jint process(JNIEnv *env, jclass clazz,
             jlong nativeHandel,
             jbyteArray inBuffer, jint inSize,
             jbyteArray outBuffer, jint outBufferSize) {
    jboolean isInCopy;
    jbyte *inBytes = env->GetByteArrayElements(inBuffer, &isInCopy);

    jboolean isOutBufCopy;
    jbyte *outBytes = env->GetByteArrayElements(outBuffer, &isOutBufCopy);

    LOGV(" %s isInCopy %s isOutCopy %s",
         __FUNCTION__,
         jbool2str(isInCopy),
         jbool2str(isOutBufCopy));

    CVoiceShift *ins = reinterpret_cast<CVoiceShift *>(nativeHandel);

    jint ret = ins->Process(reinterpret_cast<char *>(inBytes), inSize,
                            reinterpret_cast<char *>(outBytes), outBufferSize);

    env->ReleaseByteArrayElements(inBuffer, inBytes, JNI_ABORT);
    env->ReleaseByteArrayElements(outBuffer, outBytes, 0);

    return ret;
}

/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaVoiceShift
 * Method:    private static int getIdRange(long nativeHandel, int[] outMaxIdAndMinId)
 * Signature: (J[I)I
 */
jint getIdRange(JNIEnv *env, jclass clazz, jlong nativeHandel, jintArray outMaxIdAndMinId) {
    CVoiceShift *ins = reinterpret_cast<CVoiceShift *>(nativeHandel);

    jboolean isCopy;
    jint *out2 = env->GetIntArrayElements(outMaxIdAndMinId, &isCopy);
    LOGV("%s isCopy %s", __func__, jbool2str(isCopy));

    jint ret = ins->GetIdRange(out2, out2 + 1);

    env->ReleaseIntArrayElements(outMaxIdAndMinId, out2, 0);
    return ret;
}


/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaVoiceShift
 * Method:    private static int getIdDefault(long nativeHandel)
 * Signature: (J)I
 */
jint getIdDefault(JNIEnv *env, jclass clazz, jlong nativeHandel) {
    CVoiceShift *ins = reinterpret_cast<CVoiceShift *>(nativeHandel);
    return ins->GetIdDefault();
}


/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaVoiceShift
 * Method:    private static int setTypeId(long nativeHandel, int typeId)
 * Signature: (JI)I
 */
jint setTypeId(JNIEnv *env, jclass clazz, jlong nativeHandel, jint typeId) {
    CVoiceShift *ins = reinterpret_cast<CVoiceShift *>(nativeHandel);
    return ins->SetTypeId(typeId);
}


/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaVoiceShift
 * Method:    private static int getTypeId(long nativeHandel)
 * Signature: (J)I
 */
jint getTypeId(JNIEnv *env, jclass clazz, jlong nativeHandel) {
    CVoiceShift *ins = reinterpret_cast<CVoiceShift *>(nativeHandel);
    return ins->GetTypeId();
}


/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaVoiceShift
 * Method:    private static java.lang.String getNameById(long nativeHandel, int typeId)
 * Signature: (JI)Ljava/lang/String;
 */
jstring getNameById(JNIEnv *env, jclass clazz, jlong nativeHandel, jint typeId) {
    CVoiceShift *ins = reinterpret_cast<CVoiceShift *>(nativeHandel);
    char *name = ins->GetNameById(typeId);
    return env->NewStringUTF(name);
}


/*
 * Class:     com_young_jnirawbytetest_audiotest_KalaVoiceShift
 * Method:    private static void release(long nativeHandel)
 * Signature: (J)V
 */
void release(JNIEnv *env, jclass clazz, jlong nativeHandel) {
    CVoiceShift *ins = reinterpret_cast<CVoiceShift *>(nativeHandel);
    delete ins;
    return;
}

static const JNINativeMethod gsNativeMethods[] = {
        {
                .name = const_cast<char *>("create"),
                .signature = const_cast<char *>("(II)J"),
                .fnPtr = reinterpret_cast<void *>(create)
        },
        {
                /* method name      */ const_cast<char *>("process"),
                /* method signature */ const_cast<char *>("(J[BI[BI)I"),
                /* function pointer */ reinterpret_cast<void *>(process)
        },
        {
                /* method name      */ const_cast<char *>("getIdRange"),
                /* method signature */ const_cast<char *>("(J[I)I"),
                /* function pointer */ reinterpret_cast<void *>(getIdRange)
        },
        {
                /* method name      */ const_cast<char *>("getIdDefault"),
                /* method signature */ const_cast<char *>("(J)I"),
                /* function pointer */ reinterpret_cast<void *>(getIdDefault)
        },
        {
                /* method name      */ const_cast<char *>("setTypeId"),
                /* method signature */ const_cast<char *>("(JI)I"),
                /* function pointer */ reinterpret_cast<void *>(setTypeId)
        },
        {
                /* method name      */ const_cast<char *>("getTypeId"),
                /* method signature */ const_cast<char *>("(J)I"),
                /* function pointer */ reinterpret_cast<void *>(getTypeId)
        },
        {
                /* method name      */ const_cast<char *>("getNameById"),
                /* method signature */ const_cast<char *>("(JI)Ljava/lang/String;"),
                /* function pointer */ reinterpret_cast<void *>(getNameById)
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
        LOGI("KalaShift registerNativeFunction");
    jclass clazz = env->FindClass(FULL_CLASS_NAME);
    return clazz != nullptr
           && 0 == env->RegisterNatives(clazz, gsNativeMethods, gsMethodCount);
}


} //endof namespace KalaVoiceShift

