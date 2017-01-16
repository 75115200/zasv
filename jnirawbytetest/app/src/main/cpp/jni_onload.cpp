#include <android/log.h>
#include "kge/src/KalaMix.h"
#include "kge/src/KalaVoiceShift.h"
#include "kge/src/KalaToneShift.h"
#include "kge/src/KalaAudioGain.h"
#include "kge/src/KalaReverb.h"
#include "kge/src/KalaVolumeScaler.h"
#include "kge/src/KalaClean.h"
#include "kge/src/JniLocalRefTest.h"

#define LOGV(...)   __android_log_print((int)ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...)   __android_log_print((int)ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)   __android_log_print((int)ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...)   __android_log_print((int)ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...)   __android_log_print((int)ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


//change to whatever you like
static constexpr auto LOG_TAG = "AudioEffect";

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env),
                   JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    if (KalaClean::registerNativeFunctions(env)
        && KalaMix::registerNativeFunctions(env)
        && KalaVoiceShift::registerNativeFunctions(env)
        && KalaToneShift::registerNativeFunctions(env)
        && KalaAudioGain::registerNativeFunctions(env)
        && KalaReverb::registerNativeFunctions(env)
        && KalaVolumeScaler::registerNativeFunctions(env)
        && JniLocalRefTest::registerNativeFunctions(env)) {

        LOGI("%s registerNativeFunction success", __FUNCTION__);
        return JNI_VERSION_1_6;
    } else {
        LOGI("%s registerNativeFunction failed", __FUNCTION__);
        return -1;
    }
}