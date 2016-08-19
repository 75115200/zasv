/************************************************************************/
/* voice shift and voice shift                                           */
/* written by ethanzhao,  6-17,2014                                     */
/************************************************************************/
#ifndef C_VOICE_SHIFT_H
#define C_VOICE_SHIFT_H

#include "KalaInterfaces.h"

#define KALA_VOICE_SHIFT_NO_EFFECT	0		// Original (No Effect)
#define KALA_VOICE_SHIFT_SOPRANO	1		// Soprano
#define KALA_VOICE_SHIFT_BASSO		2		// Basso
#define KALA_VOICE_SHIFT_BABY		3		// Baby
#define KALA_VOICE_SHIFT_AUTOTUNE	4       // Autotune
#define KALA_VOICE_SHIFT_METAL		5		// metal
#define KALA_VOICE_SHIFT_CHORUS		6		// chorus


/* change voice style */
class LIB_KALAAUDIOBASE_API CVoiceShift:public IKalaVoiceShift
{
public:
	 int  Init			(int sampeRate, int channel, char* noteMem, int noteSize);	
	 void Uninit		( );

	 int  GetIdRange	( int* maxId, int* minId);		// get id range
	 int  GetIdDefault	( );							// get default id 
	 int  SetTypeId		( int typeID);					// set effect id
	 int  GetTypeId		( );							// get id now
	 char*GetNameById	( int typeID);					// get id name strings.

	 /* process, return the output real size after processing.        */
	 int Process(char* inBuffer, int inSize, char* outBuffer, int outSize);
	 int SetKeyShift(int key_shift_value);					// when pitch shift by user, send the value for score.
	 int GetAutoTuneLatency();

private:
	//int ProcessDog	(char* inBuffer, int inSize, char* outBuffer, int outSize);

private:
	int m_iId;				// id
	int m_iChannel;			// sample channel, 1 for mono, 2 for stereo.
	int m_iSampleRate;		// sample rate.

	int m_pass_num;			// pass number;
	float m_factor;			// factor;
	float m_step;			// step;

	void* pVoice;			//  
	void* m_pElecVoice;     //
	void* m_pMetal;
	void* m_pChorus;

};

#endif

