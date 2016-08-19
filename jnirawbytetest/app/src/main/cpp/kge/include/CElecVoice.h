#ifndef __ELEC_VOICE_H_
#define __ELEC_VOICE_H_
#include "CnotePlay.h"
#include "CFilters.h"



class CElecVoice
{
public:
    int Init(const char* noteFile, int samplerate, int channels);
	int Init(int samplerate, int channels, char* noteMem, int noteSize);
    int process(char *inData, char *outData, unsigned int size);
    void UnInit();
	int UpdateScale(int scale);
private:
    int processMono(char *inData, char *outData, unsigned int sampleSize);
private:
    void* m_autotune;
    int m_channels;
	CnoteInfo m_noteInfo;
	CFilters m_filter;
	int m_haveNote;
};


#endif // !__ELEC_VOICE_H_


