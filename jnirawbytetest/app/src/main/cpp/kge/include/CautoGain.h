#ifndef KALA_AUTO_GAIN_H
#define KALA_AUTO_GAIN_H

#include "KalaInterfaces.h"
#include "KaAudioBuffer.h"


/* song de-noise interface */
class LIB_KALAAUDIOBASE_API CautoGain:public IKalaGain
{
public:

	// support mono and stereo now.
	int  Init(int inSampleRate, int inChannel);	// set sample rate and channel;
	void Uninit( );	// uninit

	// process input buffer and output size.
	int Process(char* inBuffer, int inSize);
	
private:
	int calHanning	(float*pHanning, int iLen );				// cal hanning win by len;
	int doOla		(short* pDst, short* pSrc, int iLen);		// do ola, and set result in dst;
	int mallocBufs	( );										// malloc buffers for all;
	int freeBufs	( );										// free buffers;
	int processFrame(short* pSample, int iLen);					// process one frame.
	int vadetection	(short* pSample, int iLen);			
	int ProcessMono (char* inBuffer, int inSize);				// process mono;

private:

	// frame info
	int m_frame_len;	// frame len in number, not in size, only for mono here.
	int m_ola_len;		// ola length in number, not in size, only for mono here.

	// audio info
	int m_sample_rate;
	int m_channel;

	// for store
	CpAudio* m_buffer_in;	// buffer in;
	CpAudio* m_buffer_out;	// buffer out;

	float*	m_f_win;		// win data;

	float  m_rate;			//
	vector<int> m_power;	//

};



#endif
