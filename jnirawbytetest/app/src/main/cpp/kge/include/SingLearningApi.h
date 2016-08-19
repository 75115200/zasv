
#ifndef _SING_LEARNING_API_H_
#define _SING_LEARNING_API_H_

#include "KalaInterfaces.h"

class LIB_KALAAUDIOBASE_API CSingLearning : public ISingLearning
{
public:
	CSingLearning();
	~CSingLearning();

public:
	int Init(const char* szConfigFile, int nSampleRate);		
	void Uninit();
	int SetChannels(int nChannelNum);

	int CheckResource(const char* szNoteStr, int nNoteSize, const char* szQrcStr, int nQrcSize);
	int CreateSession(const char* szNoteStr, int nNoteSize, const char* szQrcStr, int nQrcSize);	
	void DestorySession();

	int StartSession(int nBeginTime_ms, int nEndTime_ms);	
	void StopSession();

	int PutBuffer(char* pBuffer, int nBufferSize, bool& bLastSent);	
	int PutBuffer(char* pBuffer, int nBufferSize, int nTimeStamp_ms);	
	int GetResult(int& nCurSentIndex, EScoreResultType& nScoreType, std::vector<EWordResultType>& aWordResultType);
	int GetLastResult(EScoreResultType& nScoreType);

private:
	int PutBufferIn(char* pBuffer, int nBufferSize, bool& bLastSent);
	int PutBufferIn(char* pBuffer, int nBufferSize, int nTimeStamp_ms);
};

#endif // _SING_LEARNING_API_H_
