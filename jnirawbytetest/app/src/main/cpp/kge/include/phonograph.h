#ifndef KALA_AUDIOBASE_PHONOGRAPH_H
#define KALA_AUDIOBASE_PHONOGRAPH_H

#include "KalaInterfaces.h"
#include <vector>

class LIB_KALAAUDIOBASE_API CPhonograph : public IKalaDspProcessor
{
public:
    CPhonograph();
    virtual ~CPhonograph();

	int Init(int inSampleRate, int inChannel);	// set sample rate and channel;
	void Uninit();	// uninit

	// process input buffer and output size.
	int Process(char* inBuffer, int inSize);

private:
    void* handles;
    int m_samplerate;
    int m_channels;
    std::vector<float> data;
};
#endif
