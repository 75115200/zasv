#include "kge/src/KalaClean2.h"
#include "kge/src/KalaMix.h"
#include "kge/src/KalaVoiceShift.h"
#include "kge/src/KalaToneShift.h"
#include "kge/src/KalaAudioGain.h"
#include "kge/src/KalaReverb.h"
#include "kge/src/KalaVolumeScaler.h"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env),
                   JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    KalaClean2::registerNativeFunctions(env);
    KalaMix::registerNativeFunctions(env);
    KalaVoiceShift::registerNativeFunctions(env);
    KalaToneShift::registerNativeFunctions(env);
    KalaAudioGain::registerNativeFunctions(env);
    KalaReverb::registerNativeFunctions(env);
    KalaVolumeScaler::registerNativeFunctions(env);

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {

}