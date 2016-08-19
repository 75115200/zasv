#ifndef __AL_REVERB_H_
#define __AL_REVERB_H_
#include <stdio.h>
#include "KaAudioBuffer.h"
#include "KalaInterfaces.h"
#include "phonograph.h"
#include "CFilters.h"


// #define KALA_VB_NO_EFFECT				10		// no
// #define KALA_VB_GENERIC					11		// generic, KTV
// #define KALA_VB_SEWERPIPE				12		// sewerpipe, magnetic
// #define KALA_VB_FOREST					13		// forest, ethereal
// #define KALA_VB_CITY_ABANDONED			14		// city abandoned, sweet
// #define KALA_VB_CAVE					15		// cave, warm
// #define KALA_VB_DIZZY					16		// dizzy
// #define KALA_VB_SPORT_FULLSTADIUM		17		// sport fullstadium, distant
// #define KALA_VB_PHONOGRAPH_GENERIC		18		// phonograph + generic

#define KALA_VB_NO_EFFECT				10		// no effect
#define KALA_VB_KTV_V30					11		// KTV, change to v1.5's ktv .
#define KALA_VB_WARM					12		// warm, wennuan
#define KALA_VB_MAGNETIC				13		// magnetic, cixing
#define KALA_VB_ETHEREAL				14		// ethereal, kongling
#define KALA_VB_DISTANT					15		// distant, youyuan
#define KALA_VB_DIZZY					16		// dizzy, mihuan
#define KALA_VB_PHONOGRAPH				17		// phonograph, laochangpian
#define KALA_VB_PHONOGRAPH_GENERIC		18		// not used, discard.

class CALReverb : public IKalaReverb
{
public:

    int  Init( int sampeRate, int channel );
    void Uninit();
	void GetIdRange(int* maxVal, int* minVal);
	int  GetIdDefault();

	int  SetTypeId		( int typeID);		
	int  GetTypeId		();
	char*GetNameById	( int typeID);
	int Process(char* inBuffer, int inSize, char* outBuffer, int outSize);
    

private:
	int  ProcessOneBuffer (char *inBuffer, int inSize);

	int BlockProcess(char *inBuffer, int inSize);
	int SetReverb(int reverbIndex);
	char CreateAuxEffectSlot(unsigned int *puiAuxEffectSlot);
	char CreateEffect(unsigned int *puiEffect, int eEffectType);
	char SetEFXEAXReverbProperties(void *pEFXEAXReverb, unsigned int uiEffect);

private:
    unsigned int m_src;
    unsigned int m_buffers[2];
	unsigned int m_uiEffect;
    unsigned int m_new_buffer;
    int m_format;
    unsigned int m_frequency;
    int m_bis;
    unsigned int m_channel;
    unsigned int m_devtype;
    void *m_pDevice;
    unsigned int m_uiEffectSlot;
    int m_firstTime;
	int m_id;
	int m_preid;

    CpAudio m_cached_samples;
    CpAudio m_preprocessed_samples;
	CPhonograph m_phonograph;
	CFilters m_filters;

	void* m_old_reverb;

	short *m_tempBuffer;

	short *m_process_buffer;

};

#endif
