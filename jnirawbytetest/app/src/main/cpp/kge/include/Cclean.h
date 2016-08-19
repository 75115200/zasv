#ifndef KALA_CLEAN_NOISE
#define KALA_CLEAN_NOISE


#include "KalaInterfaces.h"


/* song de-noise interface */
class LIB_KALAAUDIOBASE_API Cclean:public IKalaClean
{
public:
	int  Init(int inSampleRate, int inChannel);	// set sample rate and channel;
	void Uninit( );	// uninit

	//void Process(char* inBuffer, int inSize, char* outBuffer, int outSize);	// process
	int Process(char* inBuffer, int inSize);

private:
	int openGainRepair	(int bOpen);		// set 1 to open gain repair after filter. 0 to close;
	int doGainRepair	(char* inBuffer, int inSize, float dest_gain, float src_gain );	// to gain repair 
	float calShortGain	(char* inBuffer, int inSize);	//		

private:
	int m_nchannel;			// channel;
	int m_nsample_rate;		// sample rate;
	int m_fc;				// FC;
	int m_taps;				// taps;
	int m_frm_num;			// frame length;

	// for gain repair;
	int m_b_gain_repair;	// gain repair;
	float m_gain_times_last;	// last frame;
	float m_gain_times_step;	// gain step;

	short* m_pBuffer;		// buffer;
	void* m_filter;			// 


};




#endif

