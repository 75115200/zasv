#ifndef C_LASS_MIX_SOUND_MONO_ONLY_H
#define C_LASS_MIX_SOUND_MONO_ONLY_H

#include "KalaInterfaces.h"
#include <vector>



/* just deal with mono, don't use it for stereo */
class LIB_KALAAUDIOBASE_API CMixSoundOnlyMono
{
public:
	int  Init( int sampeRate, int channel );
	void Uninit();


	/* deal with buffer, two mono input, 1 stereo output. make sure the output buffer size >= 2* max(left, right) */
	int  Process(char* leftChannel, int leftSize,
		char* rightChannel,int rightSize,
		char* outBuffer,	 int outSize);

	/* deal with buffer, two mono input, 1 mono output. make sure the output buffer size <= min(left, right) */
	//int  ProcessMono	(char* leftChannel, int leftSize,
	//	char* rightChannel,int rightSize,
	//	char* outMono, int outSize);

	/* add */
	int GetVolumeRange	(int* maxVolume, int* minVolume);	// get volume range, the same for left and right channel.
	int GetVolumeDefault(int* volumeDefault);				// get volume value default;
	int GetDelayDefault	(int* delayMs);						// get default delay value in ms.
	int Reset			();									// reset delay and volume to default value.

	/* get interface */
	void GetDelayRange  ( int* maxDelay, int* minDelay);	// get delay range in ms
	int  GetDelay		();									// get delay parameter in ms
	int	 GetLeftVolume	();									// get left volume mix volume rate.
	int	 GetRightVolume	();									// get right volume mix volume rate.

	/* set interface */
	int  SetDelay		(int iMs   );						// set delay in ms. delay means right channel delay. default: 0.
	int	 SetLeftVolume	(int iValue);						// set left volume ,[0,200],default: 100 mean no volume change.
	int	 SetRightVolume	(int iValue);						// set right volume,[0,200],default: 100 mean no volume change.

private:
	int MixTwo2WithRate3	(char* pDst,float frateDst, char* pSrc, float frateSrc,int inSize);\
		int RepairMidBuffer		( ); // repair data in mid buffer

private:
	int m_iLeftVolume;		// volume left 
	int m_iRightVolume;		// volume right
	int m_iDelayMs;			// delay ms

	//char* pMonoDelay;		// delay buffer, mono.
	//CpAudio* m_pBuffer;		// buffer
	void* m_pAudioBuf;		// audio buffer;

	int m_max_in_left_channel;
	int m_max_in_right_channel;
	int m_cnt;
	float m_both_factor;
	float m_factor_last;	//

	int* m_p_mid_buffer;		// mid buffer to output
	int m_mid_buffer_len;	// mid buffer len;
	int m_history_len;		// history data length;


};


#endif
