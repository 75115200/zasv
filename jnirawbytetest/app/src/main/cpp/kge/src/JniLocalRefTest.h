/**
 * File generated by Jenny -- https://github.com/LanderlYoung/Jenny
 *
 * DO NOT EDIT THIS FILE WITHOUT COPYING TO YOUR SRC DIRECTORY.
 *
 * For bug report, please refer to github issue tracker https://github.com/LanderlYoung/Jenny/issues,
 * or contact author landerlyoung@gmail.com.
 */

/* C++ header file for class com.young.jnirawbytetest.audiotest.JniLocalRefTest */
#pragma once

#include <jni.h>

namespace  JniLocalRefTest {

//DO NOT modify
static constexpr auto FULL_CLASS_NAME = "com/young/jnirawbytetest/audiotest/JniLocalRefTest";



/*
 * Class:     com_young_jnirawbytetest_audiotest_JniLocalRefTest
 * Method:    public static java.lang.String process(java.lang.Object[] arr)
 * Signature: ([Ljava/lang/Object;)Ljava/lang/String;
 */
jstring process(JNIEnv *env, jclass clazz, jobjectArray arr);




/**
 * register Native functions
 * @returns success or not
 */
bool registerNativeFunctions(JNIEnv *env);

} //endof namespace JniLocalRefTest