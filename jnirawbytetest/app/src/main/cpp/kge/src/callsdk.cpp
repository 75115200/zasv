/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include "CKalaVolume.h"
#include "CReverb4.h"
#include "CVoiceShift.h"
#include "CVolumeScaler.h"
#include "CautoGain.h"

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */

 extern "C" {
 // extern begin

 ////////////////////////////////////////// GetVolume /////////////////////////////////////

 jlong Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_createGetVolume(JNIEnv* env, jobject thiz)
 {
     CKalaVolume * pGetVolume = new CKalaVolume();
     return reinterpret_cast<jlong>(pGetVolume);
 }

 void Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_releaseGetVolume(JNIEnv* env, jobject thiz, jlong handle)
 {
     CKalaVolume *pGetVolume = reinterpret_cast<CKalaVolume *>(handle);
     if(pGetVolume) {
         delete pGetVolume;
     }
 }

 jint
Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_getVolume( JNIEnv* env, jobject thiz, jlong handle, jbyteArray data, jint size)
{
    CKalaVolume *pGetVolume = reinterpret_cast<CKalaVolume *>(handle);
    jboolean isCopy;
    jbyte *pcmData = env->GetByteArrayElements(data, &isCopy);
    int outVolume = 0;
    pGetVolume->Process(reinterpret_cast<char*>(pcmData), (int)size, &outVolume);
    env->ReleaseByteArrayElements(data, pcmData, 0);
    return (jint)outVolume;
}

////////////////////////////////////////// reverb4 ////////////////////////////////////////////

  jint
Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_doReverb4(JNIEnv* env, jobject thiz,
                            jlong handle, jint typeID,
                            jbyteArray dataIn, jint sizeIn, jbyteArray dataOut, jint sizeOut)
{
    CReverb4 *pReverb = reinterpret_cast<CReverb4 *>(handle);

    if(pReverb != NULL)
    {
        jboolean isCopy;
        jbyte *pcmDataIn = env->GetByteArrayElements(dataIn, &isCopy);
        jbyte *pcmDataOut = env->GetByteArrayElements(dataOut, &isCopy);
        pReverb->SetTypeId((int)typeID);
        pReverb->Process(reinterpret_cast<char *>(pcmDataIn), (int)sizeIn, reinterpret_cast<char *>(pcmDataOut), (int)sizeOut);
        env->ReleaseByteArrayElements(dataIn, pcmDataIn, 0);
        env->ReleaseByteArrayElements(dataOut, pcmDataOut, 0);
    }
    return 0;
}

jlong Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_createReverb4(JNIEnv* env, jobject thiz,
                                                             jint sampleRate, jint channel)
{
    CReverb4 * pReverb = new CReverb4();
    pReverb->Init((int)sampleRate, (int)channel);
    return reinterpret_cast<jlong>(pReverb);
}

void Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_releaseReverb4(JNIEnv* env, jobject thiz, jlong handle)
{
    CReverb4 *pReverb = reinterpret_cast<CReverb4 *>(handle);
    if(pReverb) {
        pReverb->Uninit();
        delete pReverb;
    }
}

////////////////////////////////////////// VoiceShift ////////////////////////////////////////////

  jint
Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_doVoiceShift(JNIEnv* env, jobject thiz,
                            jlong handle, jint typeID,
                            jbyteArray dataIn, jint sizeIn, jbyteArray dataOut, jint sizeOut)
{
        CVoiceShift *pVoiceShift = reinterpret_cast<CVoiceShift *>(handle);

        if(pVoiceShift != NULL)
        {
            jboolean isCopy;
            jbyte *pcmDataIn = env->GetByteArrayElements(dataIn, &isCopy);
            jbyte *pcmDataOut = env->GetByteArrayElements(dataOut, &isCopy);
            pVoiceShift->SetTypeId((int)typeID);
            pVoiceShift->Process(reinterpret_cast<char *>(pcmDataIn), (int)sizeIn, reinterpret_cast<char *>(pcmDataOut), (int)sizeOut);
            env->ReleaseByteArrayElements(dataIn, pcmDataIn, 0);
            env->ReleaseByteArrayElements(dataOut, pcmDataOut, 0);
        }
        return 0;
}

jlong Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_createVoiceShift(JNIEnv* env, jobject thiz,
                                                             jint sampleRate, jint channel)
{
    CVoiceShift * pVoiceShift = new CVoiceShift();
    pVoiceShift->Init((int)sampleRate, (int)channel, NULL, 0);
    return reinterpret_cast<jlong>(pVoiceShift);
}

void Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_releaseVoiceShift(JNIEnv* env, jobject thiz, jlong handle)
{
    CVoiceShift *pVoiceShift = reinterpret_cast<CVoiceShift *>(handle);
    if(pVoiceShift) {
        pVoiceShift->Uninit();
        delete pVoiceShift;
    }
}

////////////////////////////////////////// VolumeScalar ////////////////////////////////////////////

  jint
Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_doVolumeScalar(JNIEnv* env, jobject thiz,
                            jlong handle, jint factor,
                            jbyteArray dataIn, jint sizeIn)
{
        CKalaVolumeScaler *pVolumeScalar = reinterpret_cast<CKalaVolumeScaler *>(handle);

        if(pVolumeScalar != NULL)
        {
            jboolean isCopy;
            jbyte *pcmDataIn = env->GetByteArrayElements(dataIn, &isCopy);
            pVolumeScalar->SetScaleFactor((int)factor);
            pVolumeScalar->Process(reinterpret_cast<char *>(pcmDataIn), (int)sizeIn);
            env->ReleaseByteArrayElements(dataIn, pcmDataIn, 0);
        }
        return 0;
}

jlong Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_createVolumeScalar(JNIEnv* env, jobject thiz,
                                                             jint sampleRate, jint channel)
{
    CKalaVolumeScaler * pVolumeScalar = new CKalaVolumeScaler();
    pVolumeScalar->Init((int)sampleRate, (int)channel);
    return reinterpret_cast<jlong>(pVolumeScalar);
}

void Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_releaseVolumeScalar(JNIEnv* env, jobject thiz, jlong handle)
{
    CKalaVolumeScaler *pVolumeScalar = reinterpret_cast<CKalaVolumeScaler *>(handle);
    if(pVolumeScalar) {
        pVolumeScalar->Uninit();
        delete pVolumeScalar;
    }
}


////////////////////////////////////////// AutoGain ////////////////////////////////////////////

  jint
Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_doAutoGain(JNIEnv* env, jobject thiz,
                            jlong handle,
                            jbyteArray dataIn, jint sizeIn)
{
        CautoGain *pAutoGain = reinterpret_cast<CautoGain *>(handle);

        if(pAutoGain != NULL)
        {
            jboolean isCopy;
            jbyte *pcmDataIn = env->GetByteArrayElements(dataIn, &isCopy);
            pAutoGain->Process(reinterpret_cast<char *>(pcmDataIn), (int)sizeIn);
            env->ReleaseByteArrayElements(dataIn, pcmDataIn, 0);
        }
        return 0;
}

jlong Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_createAutoGain(JNIEnv* env, jobject thiz,
                                                             jint sampleRate, jint channel)
{
    CautoGain * pAutoGain = new CautoGain();
    pAutoGain->Init((int)sampleRate, (int)channel);
    return reinterpret_cast<jlong>(pAutoGain);
}

void Java_com_young_jnirawbytetest_audiotest_TestAudioEffectFragment_releaseAutoGain(JNIEnv* env, jobject thiz, jlong handle)
{
    CautoGain *pAutoGain = reinterpret_cast<CautoGain *>(handle);
    if(pAutoGain) {
        pAutoGain->Uninit();
        delete pAutoGain;
    }
}

//extern end
}

