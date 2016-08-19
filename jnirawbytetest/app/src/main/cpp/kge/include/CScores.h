#ifndef SONG_SCORE_SCORES_H
#define SONG_SCORE_SCORES_H

#include "KalaInterfaces.h"
#include "KaAudioBuffer.h"
#include "CFrameAxis.h"
#include "CSectionCfg.h"

class LIB_KALAAUDIOBASE_API CScores:public IKalaScore
{
public:
	int  SetChannels(int channels); // default is 1 (Mono)
	int  SetSamplerate(int samplerate); // default is 44100
	int  Init		( char* noteFile, vector<int> sentences );				// note file here and sentence vector input.
	int  Init		( char* noteMem, int memSize, vector<int> sentence);	// note memory here and sentence vector input.

	// for section singing, add section memory & memory size & singer string additional. just for ios.
	int  Init		( char* noteMem, int memSize, vector<int> sentences, char* section_memory, int section_mem_size,char* role_string);
	// for section singing, add section memory & memory size additional, just for android.
	int  Init		(char* noteMem, int memSize, vector<int> sentences, vector<int>sentence_to_sing);	

	void Uninit		( );											// uninit
	int  Process	( char* inBuffer, int inSize, int timeStamp);	// input mono PCM data and time position in ms.

	int  GetNoteRange		(int* maxNote, int* minNote);			// get note range to show.
	void GetScoreRange		(int* maxScore, int* minScore);			// get the max and min score supported in sentence.
	int  GetNoteSing		(int* iNote,int*bIsHunt );				// get the singer's note now, and tell if hunt. 1 for yes, 0 for no.

	int  GetNotePlay		(vector<noteVector>*notes);				// get note array to show
	int  GetLastScore		( );									// call this function to get a new sentence score, if no new data, return -1.
	int  GetTotalScore		( );									// get total score
	int  GetAllScores		(vector<int>* scores);					// get all scores of sentence.

	int  OpenOrigSing		( int bOpen );							// if sing with original music accompaniment,1 for open,0 for close. set 1 will decrease scores.   	 	

	int  Reseek		(int time_ms);									// reset time position by specified time, in ms;
	int  SetKeyShift		( int key_shift_value);					// when pitch shift by user, send the value for score.

private:
	CpAudio*	m_pbuffer;			// audio buffer;
	CframeAxis2 m_time_axis;		// time axis;
	CSectionUser m_section_info;	// section singing, input section info.

	int m_channels;
	short* m_mono_data;
	int m_mono_allocated;

	void init();
	
	int ProcessMono(char *inBuffer, int inSize, int timeStamp);
};




#endif
