#ifndef KALA_AUDIO_BUFFER_H
#define KALA_AUDIO_BUFFER_H

#include "MSdcommon.h"

//#ifdef __cplusplus
//extern "C"{
//#endif

/*
* struct of audio sample buffer.
*/
typedef struct tagChirpAudio{

	int iSampleRate;	// sample rate of the audio, output for encode, and input for decode.
	int iChannel;		// channel of the audio, output for encode, and input for decode.
	int iBufferLen;		// buffer length
	int iUseLen;        // used length

	Asample* pSample;	// audio samples, output for encode, and input for decode.

}CpAudio, *PCpAudio;

/* 
* Des:
*	input buffer samples.
*  Return:
*	0 for successful, else for error.
*/
int BufferInputSamples	(CpAudio* pAudio, Asample* pIn,  int iSampleLen);

/* Des:
*	output sample in audio buffer by specified length, if no enough data, return the real length.
*  Return:
*	the real length of data output, negitive data for errors.
*/
int BufferOutputSamples	(CpAudio* pAudio, Asample* pOut, int iSampleLen);

/*
* Des:
*	remove samples in buffer head by specified length, if no so much, remove all sample in buffer
* Return:
*	return the real length of data removed.
*/
int BufferRemoveSamples	(CpAudio* pAudio, int iRemoveLen);

/*
* Des:
*	send sample of zero, as new data input, by specified length.
* Return:
*	0 for successful, else for errors.
*/
int BufferFillZeros		(CpAudio* pAudio, int iZeroLen);
//
//#ifdef __cplusplus
//};
//#endif

#endif

