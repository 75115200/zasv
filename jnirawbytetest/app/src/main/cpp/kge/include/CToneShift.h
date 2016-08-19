/************************************************************************/
/* tone shift                                          */
/* written by ethanzhao,  6-16,2014                                     */
/************************************************************************/
#ifndef C_TONE_SHIFT_H
#define C_TONE_SHIFT_H

#include "KalaInterfaces.h"

/* change tone style */
class LIB_KALAAUDIOBASE_API CToneShift:public IKalaToneShift
{
public:
	int  Init			(int sampeRate, int channel);	
	void Uninit			( );

	int  GetShiftRange	( int* maxVal, int* minVal);	// get shift range. [-12,+12]
	int  GetShiftDefault( );							// get shift default value. maybe 0.
	int  SetShiftValue	( int shiftVal);				// set shift value now.
	int  GetShiftValue	( );				// get shift value now.

	/* process, return the output real size after processing.        */
	int  Process(char* inBuffer, int inSize, char* outBuffer, int outSize);	

private:
	int m_shift_value;		// shift value.
	int m_iChannel;			// sample channel, 1 for mono, 2 for stereo.
	int m_iSampleRate;		// sample rate.

	void* pTone;			// 
};


#endif

