/************************************************************************/
/* volume sclaer interface                                                   */
/* last modified by ethanzhao, 4-27,2016.                               */
/* copy right reserved.                                                 */
/************************************************************************/
#ifndef C_KALA_VOLUME_SCALER_Z_H
#define C_KALA_VOLUME_SCALER_Z_H

#include "KalaInterfaces.h"
#include "MSdcommon.h"
#include "Climit.h"

/* volume scale, just for kg v3.5, only short pcm support, stereo and mono */
class LIB_KALAAUDIOBASE_API CKalaVolumeScaler:public IKalaVolumeScaler
{
public:
	 int  Init(int inSampleRate, int inChannel );	// set sample rate and channel and buffer size to process;
	 void Uninit();	// uninit
	 int  SetScaleFactor	(int iValue);    // set scale factor, [0,200], 100 for no change.
	 int  Process(char* inBuffer, int inSize);	// process

private:
	float m_fscaler;	// scaler factor, float;	
	int m_sample_rate;	// sample rate;
	int m_channels;		// channels input;
	ClimitMono* m_limiter_L;
	ClimitMono* m_limiter_R;

};


#endif





