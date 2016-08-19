#ifndef KALABASE_C_LIMIT_FILE_H
#define KALABASE_C_LIMIT_FILE_H

#include "MSdcommon.h"
#include "KaAudioBuffer.h"

/* limit data (int type ) into [-32768, 32767], both input and output are int type */
class ClimitMono
{
public:
	int  Init(int inSampleRate, int inChannel );	// set sample rate and channel and buffer size to process;
	void Uninit();	// uninit	
	int  Process(int* inBuffer, int iLen);			// limit int data to [-32768, 32767] 

private:
	float m_fLast_factor;

};

#endif

