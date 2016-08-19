#ifndef AUDIO_SECTION_INFO_H
#define AUDIO_SECTION_INFO_H

#include <vector>
#include <string>
#include "MSdcommon.h"

using namespace std;

typedef struct _tag_sentence_info
{
	int sentence_id;
	int sentence_start_ms;
	int sentence_end_ms;
	string singer;		// singer A?B?C?

}SectionSingers;

//typedef struct _tagSectionABC
//{
//	vector<SentenceInfo> section_A;
//	vector<SentenceInfo> section_B;
//	vector<SentenceInfo> section_C;
//
//}SectionABC;

//typedef struct  _tagAudio_Section_Info 
//{
//
//	// singer name string, A, B,C liked
//	string m_singerA_name;
//	string m_singerB_name;	
//	string m_singerC_name;
//
//	// block
//	vector<SentTime> m_sent_A;
//	vector<SentTime> m_sent_B;
//	vector<SentTime> m_sent_C;
//
//	vector<int> m_sentence_ids_A;
//	vector<int> m_sentence_ids_B;
//	vector<int> m_sentence_ids_C;
//
//}SectionInfo;


#endif

