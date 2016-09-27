/**
* <pre>
* Author: landerlyoung@gmail.com
* Date:   2016-09-21
* Time:   16:59
* Life with Passion, Code with Creativity.
* </pre>
*/

#include <jni.h>
#include "SuperSoundWrapper.h"
#include "VoiceChangerWrapper.h"

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env),
                   JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    SuperSoundWrapper::registerNativeFunctions(env);
    VoiceChangerWrapper::registerNativeFunctions(env);
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved)
{

}
