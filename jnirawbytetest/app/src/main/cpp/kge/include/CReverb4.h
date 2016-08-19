#ifndef _C_AL_VERB_V40_VERSION_H_
#define _C_AL_VERB_V40_VERSION_H_
#include <stdio.h>
/************************************************************************/
/* Creverb4's version.                                            */
/* Create by lesterkong, 8-24,2015                                       */
/************************************************************************/
#include "KalaInterfaces.h"
#include "phonograph.h"
#include "CFilters.h"
#include "slowFlanger.h"

#define KALA_VB_NO_EFFECT_QUICKLY				10		// no effect
#define KALA_VB_KTV_V40_QUICKLY					11		// KTV, change to v1.5's ktv .
#define KALA_VB_WARM_QUICKLY					12		// warm, wennuan
#define KALA_VB_MAGNETIC_QUICKLY				13		// magnetic, cixing
#define KALA_VB_ETHEREAL_QUICKLY				14		// ethereal, kongling
#define KALA_VB_DISTANT_QUICKLY					15		// distant, youyuan
#define KALA_VB_DIZZY_QUICKLY					16		// dizzy, mihuan
#define KALA_VB_PHONOGRAPH_QUICKLY				17		// phonograph, laochangpian
#define KALA_VB_PHONOGRAPH_GENERIC_QUICKLY		18		// not used, discard.

/*
	CReverb4
*/
class LIB_KALAAUDIOBASE_API CReverb4 : public IKalaReverb
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
	int FadeLeftRight(char* inBuffer, int inSize);
	
private:
	int m_sample_rate;
	int m_channel;
    
	int m_id;
	int m_index_left;
	int m_index_right;

	int m_line_num;

	CPhonograph m_phonograph;
	CFilters m_filters;
	CSlowFlanging m_slow_flanging;
	void* m_old_reverb;
	void* m_openal_reverb;

};

#endif
