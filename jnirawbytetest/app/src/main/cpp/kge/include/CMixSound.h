#ifndef C_LASS_MIX_SOUND_H
#define C_LASS_MIX_SOUND_H

#include "KalaInterfaces.h"
#include <vector>
#include "CMixSoundMonoOnly.h"

class LIB_KALAAUDIOBASE_API CMixSound:public IKalaMix
{
public:
	int  Init( int sampeRate, int channel );
	void Uninit();

	/* deal with buffer, two mono input, 1 stereo output. make sure the output buffer size >= 2* max(left, right) */
	int  Process(char* leftChannel, int leftSize,
		char* rightChannel,int rightSize,
		char* outBuffer,	int outSize);

	/*
	music: Music Input (Stereo In)
	original:  Original Track (Stereo In)
	vocal:  Vocal(Stereo In, post-processed vocal)
	mixdown: Output of the mixdown
	size: Bytes to process
	mixvocal: True to mix the vocal to mixdown
	*/
	int ProcessSmart(const char* music, const char* original,
		const char* vocal, char* mixdown, int size, bool mixvocal);
	
	/* add */
	int GetVolumeRange	(int* maxVolume, int* minVolume);
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
	CMixSoundOnlyMono m_mixer_left;
	CMixSoundOnlyMono m_mixer_right;
	int m_channel;

	int AllocatedSamples;
	short* AltSamples;
	double mo_ratio;

	double vocal_level;
	double vocal_max;

	int AllocateMusicBuffer(int Frames);
	int Duckering(short* mixdown, const short* music, const short* original, const short* vocal, int frames);

};



#endif
