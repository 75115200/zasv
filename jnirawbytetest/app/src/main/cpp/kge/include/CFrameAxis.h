#ifndef C_TIME_AIXS_H
#define C_TIME_AIXS_H

#include <vector>
using namespace std;

#include "MSdcommon.h"
#include "CnotePlay.h"

/* block variables in sentence */
typedef struct _tagBlockSent
{
	int m_cnt;				// count of block number to call back;
	int m_cunt_not_sentence;// conut no in sentence;
	int m_blk_sub_score;	// block sub score 
	int m_blk_start;		// block start;
	int m_blk_end;			// block end;
	int m_blk_note_play;	// block note to show for ui if hunt.
	int m_blk_is_hunt;		// 1 for hunt, 0 for no.

}mBlkInfo;

/* scores used in frame axis */
typedef struct _tagScoreInfo
{
	//int m_score_total;	// total score, sum of sentences;
	int m_score_new;	// sentence score,-1 for no score, else for new sentence score here. 

	vector<int> m_score_of_sentence;	// score array for all sentence
	vector<int> m_score_note;			// score array for all sentence of note,40 in all
	vector<int> m_score_melody;			// score array for all sentence of melody, 60 in all.
	vector<int> m_score_map;			// score array for map;

	_tagScoreInfo()
	{
		m_score_new = 0;
	}

}mScoreInfo;

/* sentence zone struct */
typedef struct _tagSentenceZone
{
	int iStart_id;
	int iEnd_id;

	_tagSentenceZone()
	{
		iStart_id = iEnd_id = 0;
	}


}mSentZone;

typedef struct _tagFrameArrays 
{
	vector<mSentZone> m_sentenceZone;			// sentence zone in frame id.
	int* m_pitchArray;					// pitch array;
	int* m_sentenceMark;				// sentence mark array;
	int* m_noteArray;					// note array;

	_tagFrameArrays()
	{
		m_pitchArray = m_sentenceMark = m_noteArray = 0;
	}

}mFrameArrays;

class LIB_KALAAUDIOBASE_API CframeAxis2
{
public:

	int  init			(char* noteFile, vector<int> inSentence);				// use note file
	int  init			(char* noteMem, int memSize, vector<int> inSentence);	// use note memory
	void uninit			( );
	
	int  setTimeStamp	(int time_ms);	// set time stamp;
	int	 getFrameNow	( );			// get frame stamp current;

	int  isInSentence	( );			// return 1 if in sentence, 0 for no.
	//int	 isSentenceEnd	( );			// return 1 for end
	//int  isSentenceStart( );			// return 1 for start

	int  isHunt			(int* inote, int* bIsHunt);	// find 

	int  setPitch		(int iPv);		// set pitch value for current frame
	int  getPitch		( );			// get pitch value for current frame

	int  getLastScore	( );			// unused interface now, //get last score, if no new, return -1;
	int  getTotalScore	( );			// get total score;

	int  getAllScores	(vector<int>*scores );			// get all scores array;	
	int  setDecreaseScore	( int bDecrease );			// decrease score from now on, 1 for open, 0 for close;

	int  openSectionSing	(int bOpen, vector<int> sentence_id_to_sing);	// bOpen = 1 to open section sing, and set sentence id, and 0 for not section sing;
	
	int  setKeyShift	(int key_shift_value);

private:
	int  calScoreCurrent( );			// calculate score only this sentence.
	//int	 calTotalScore	( );			// calculate score in all.
	int  findSentenceEnd	( );			// get sentence end index.
	int  findSentenceStart	( );			// get sentence start
	int  initFrameAxis	(vector<int>inSentence);			// 
	int  initNoteInfo	(char* noteMem,int memSize);		// init note info by note memory
	int  initNoteInfo	(char* noteFile);					// init note info by note file
	int  timeMs2Id		(int ms);		// convert ms to frame id;
	int  resetPosition	(int newId);	// reset position by new id;
	int  getSentenceStat	( );

	int  doInSent		( );
	int  doSentBegin	( );
	int  doSentEnd		( );
	int  doNotInsent	( );			// do not in sentence;

	int  isTwoMatch		(int iPv, int iNv);

	int  humSingNoScore	( );
public:
	CnoteInfo m_noteInfo;

private:

	int m_frame_ms;		// frame length in ms.
	int m_frameNum;		// frame number in all
	int m_frameId_now;	// frame id now;
	int m_timestamp_last_ms;	// the time stamp last  
	int m_sentenceNum;		// sentence number in all;

	int m_b_enable_decrease;	// decrease scores from now on;

	int m_b_enable_section_sing;	// open section singing;
	vector<int> m_section_sentence_to_sing;	// sentence to sing, save the sentence id to sing.

	int m_note_frame_number;	// note frame number;

private:
	mBlkInfo		mblk;
	mFrameArrays	mArrays;
	mScoreInfo		mscores;

	int m_map_seed;		// map seed
	int m_key_shift;


};




#endif
