#ifndef KALA_CLEAN_NOISE_NEW_V3_H
#define KALA_CLEAN_NOISE_NEW_V3_H

#include "KalaInterfaces.h"
#include "KaAudioBuffer.h"


#define REQUEST_BUFFER_SIZE 320

/* song de-noise interface V2.0 */
class LIB_KALAAUDIOBASE_API CCleanNew3:public IKalaClean2
{
public:
	int  Init(int inSampleRate, int inChannel); // set sample rate and channel and buffer size to process;
	void Uninit( );	// uninit

	/* only support mono and 16bit PCM now,and the inSize must same as buffer size */
	int Process(char* inBuffer, int inSize);

private:
	int m_frame_size;
	int m_sample_rate;
	int m_channel;
    int m_capture_level;
	void* m_pstat;	

    CpAudio m_cached_samples;
    CpAudio m_preprocessed_samples;
	short* m_process_buffer;

    int BlockProcess(char* inBuffer, int inSize);
};


#endif

