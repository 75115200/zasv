#ifndef C_SING_SECTION_QRC_H
#define C_SING_SECTION_QRC_H

/************************************************************************/
/* �ֶκϳ����ܣ������ֶκϳ���QRC�ļ�                   ��             */
/* written by ethanzhao, modified 3.12,2015.                            */
/************************************************************************/

#include "MSdcommon.h"
#include <vector>
#include <string>
#include "CqrcStar2.h"
#include "SectionInfo.h"

using namespace std;



// ��ȡ�Ǻϳ���ʣ�Ȼ��ֱ�ӽ���ֳ�AB�Ρ������ϳ����֣���ʱ���ֺϳ���
class CqrcSection2
{
public:
	int init( char* qrc_file );// qrc file name.
	void uinit ( );

	//int GetWordsByTime	(string* outStr, int time_ms, int* correct_time_ms);			// get words by time ms, and return the ms corrected;
	//int GetWordsById	(string* outStr, int sentence_number);							// get words by sentence number 
	//
	//int GetHighEndFromNow	(int now_ms); // get high part end from the head time now in ms;
	//int GetIdByTime		(int time_ms);				// get sentence id by time in ms;
	//int GetIdTime	(int iID,int* iStratMs, int * iEndMs);			// get id's start ms and end ms.
	
	string* GetSingerA ( );	// ��ȡsingerA�����ƣ����С�Ů
	string* GetSingerB ( ); // ��ȡsingerB�����ƣ����С�Ů
	string* GetSingerC ( ); // ��ȡsingerC�����ƣ��ϳ���

	int GetSectionInfoA (vector<SectionSingers>* p_section);
	int GetSectionInfoB (vector<SectionSingers>* p_section);
	int GetSectionInfoC (vector<SectionSingers>* p_section);

	int GetSentenceTimeValues	(vector<int>* sentence_values);


public:
	vector<SectionSingers> m_section_A;	// section a's sentence.
	vector<SectionSingers> m_section_B;	// section b's sentence.
	vector<SectionSingers> m_section_C;	// section c's sentence.

private:
	int ParseQrcFile	(char* qrc_file);
	int ExtractSentTime	( );	// find all the sentence time and erase the string.
	int ExtractSentWords	( );	// find all the sentence words and erase the sub time.
	int RemoveEnter			(string* qrc_words ); // remove enter key in qrc words;

	//int CalSingerInfo	( );	// ��ȡsinger���ַ�������ʼ����ȣ��ϳ���Ϊÿ���˶��С�
	//int CheckMask		( );	// ȷ�Ϻϳ�qrc�ı�ʶ��

	int calSection	( );

	int findPeaks	(vector<int>* array_int, int W);


private:
	int m_sentence_number;		// sentence number;

	vector<SentTime> m_sent_time;// ���о��ӵ���ʼʱ��;
	vector<string>   m_words;	 // word;

	string m_Singer_A;			 // singer A
	string m_Singer_B;			 // singer B
	string m_Singer_C;			 // �ϳ�

};



#endif
