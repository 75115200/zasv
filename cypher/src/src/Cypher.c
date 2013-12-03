/*************************************************************************
    > File Name:     Cypher.c
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  2013/6/15 23:29:36
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Cypher.h"
#include "des.h"
#include "aes.h"
#include "rc4.h"
/*
 * Class:     Cypher
 * Method:    desKeySetUp
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_Cypher_desKeySetUp
  (JNIEnv *env, jclass obj, jbyteArray key) {
	  char *key_tmp = (char*)(*env)->GetByteArrayElements(
			  env, key, 0);
	  desKeySetUp(key_tmp);
	  (*env)->ReleaseByteArrayElements(env, key, key_tmp, 0);
  }

/*
 * Class:     Cypher
 * Method:    desEncryption
 * Signature: ([B[B[B)V
 */
JNIEXPORT void JNICALL Java_Cypher_desEncryption
  (JNIEnv *env, jobject obj,
   jbyteArray message, jbyteArray cypher) {
	  char* message_tmp =
		  (char*)(*env)->GetByteArrayElements(env, message, 0);
	  char cypher_tmp[8];

	  encryption(message_tmp, cypher_tmp);

	  (*env)->SetByteArrayRegion(env, cypher, 0, 8,  cypher_tmp);
	  (*env)->ReleaseByteArrayElements(env, message, message_tmp, 0);
  }

/*
 * Class:     Cypher
 * Method:    desDecryption
 * Signature: ([B[B[B)V
 */
JNIEXPORT void JNICALL Java_Cypher_desDecryption
  (JNIEnv *env, jobject obj,
   jbyteArray message, jbyteArray cypher) {
	  char* cypher_tmp = (char*)(*env)->GetByteArrayElements(env, cypher, 0);
	  char message_tmp[8];
	  decryption(cypher_tmp, message_tmp);
	  (*env)->SetByteArrayRegion(env, message, 0, 8,  message_tmp);
	  (*env)->ReleaseByteArrayElements(env, cypher, cypher_tmp, 0);
  }

/*
 * Class:     Cypher
 * Method:    aesKeySetUp
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_Cypher_aesKeySetUp
  (JNIEnv *env, jclass obj, jbyteArray key) {
	  char *key_tmp = (char*)(*env)->GetByteArrayElements(env, key, 0);
	  aesKeySetUp(key_tmp);
	  (*env)->ReleaseByteArrayElements(env, key, key_tmp, 0);
  }

/*
 * Class:     Cypher
 * Method:    aesEncryption
 * Signature: ([B[B)[B
 */
JNIEXPORT void JNICALL Java_Cypher_aesEncryption
  (JNIEnv *env,  jclass obj, jbyteArray message, jbyteArray cypher) {
	  char *message_tmp = (char*)(*env)->GetByteArrayElements(env, message, 0);
	  char *cypher_tmp = (char*)(*env)->GetByteArrayElements(env, cypher, 0);
	  aesEncrypt(message_tmp, cypher_tmp);
	  (*env)->SetByteArrayRegion(env, cypher, 0, 16, cypher_tmp);
	  (*env)->ReleaseByteArrayElements(env, message, message_tmp, 0);
	  (*env)->ReleaseByteArrayElements(env, cypher, cypher_tmp, 0);
  }

/*
 * Class:     Cypher
 * Method:    aesDecryption
 * Signature: ([B[B)[B
 */
JNIEXPORT void JNICALL Java_Cypher_aesDecryption
  (JNIEnv *env, jclass obj, jbyteArray message, jbyteArray cypher) {

	  char *message_tmp = (char*)(*env)->GetByteArrayElements(env, message, 0);
	  char *cypher_tmp = (char*)(*env)->GetByteArrayElements(env, cypher, 0);
	  aesDecrypt(message_tmp, cypher_tmp);
	  (*env)->SetByteArrayRegion(env, message, 0, 16, message_tmp);
	  (*env)->ReleaseByteArrayElements(env, message, message_tmp, 0);
	  (*env)->ReleaseByteArrayElements(env, cypher, cypher_tmp, 0);
  }

/*
 * Class:     Cypher
 * Method:    rc4KeySetup
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_Cypher_rc4KeySetup
  (JNIEnv *env, jclass obj, jbyteArray key) {
	  int len = (int)(*env)->GetArrayLength(env, key);
	  byte *key_tmp = (*env)->GetByteArrayElements(env, key, 0);
	  rc4KeySetUp(key_tmp, len);
	  (*env)->ReleaseByteArrayElements(env, key, key_tmp, 0);

  }

/*
 * Class:     Cypher
 * Method:    rc4GenKey
 * Signature: ()B
 */
JNIEXPORT jbyte JNICALL Java_Cypher_rc4GenKey
  (JNIEnv *env, jclass obj) {
	  jbyte k = rc4GenKey();
	  return k;
  }
