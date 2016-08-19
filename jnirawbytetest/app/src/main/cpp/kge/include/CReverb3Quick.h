#ifndef C_AL_VERB_V30_QUICK_VERSION_H
#define C_AL_VERB_V30_QUICK_VERSION_H
#include <stdio.h>
/************************************************************************/
/* Creverb3's quick version.                                            */
/* Create by ethanzhao, 8-18,2015                                       */
/************************************************************************/
#include "KaAudioBuffer.h"
#include "KalaInterfaces.h"
#include "phonograph.h"
#include "CFilters.h"

#define KALA_VB_NO_EFFECT_QUICK				10		// no effect
#define KALA_VB_KTV_V30_QUICK				11		// KTV, change to v1.5's ktv .
#define KALA_VB_WARM_QUICK					12		// warm, wennuan
#define KALA_VB_MAGNETIC_QUICK				13		// magnetic, cixing
#define KALA_VB_ETHEREAL_QUICK				14		// ethereal, kongling
#define KALA_VB_DISTANT_QUICK				15		// distant, youyuan
#define KALA_VB_DIZZY_QUICK			        16		// dizzy, mihuan
#define KALA_VB_PHONOGRAPH_QUICK			17		// phonograph, laochangpian
#define KALA_VB_PHONOGRAPH_GENERIC_QUICK	18		// not used, discard.

/*
	CALReverb's quick version.
*/
class CALReverbQuick : public IKalaReverb
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
	
private:
	int m_sample_rate;
	int m_channel;
    
	int m_id;

	CpAudio m_cached_samples;
	CpAudio m_preprocessed_samples;

	CPhonograph m_phonograph;
	CFilters m_filters;
	void* m_old_reverb;

};

#endif
