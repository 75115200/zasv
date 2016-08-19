#ifndef C_NOTE_TO_PLAY_H
#define C_NOTE_TO_PLAY_H

/************************************************************************/
/* this class input the note file and output the wav                    */
/* written by ethanzhao, modified 07.29,2014.                           */
/************************************************************************/

#include "KalaInterfaces.h"

#define KEYSTAT_RESEARCHING_MODE 0

#define KEY_IN_SUGGESTION 12

class LIB_KALAAUDIOBASE_API CnoteInfo{

public:

	int init	(char* note_file);							// use note file
	int init	(char* noteMem, int noteSize);				// use note memory read from note file.
	int uninit	();
	
	// for ui show
	int getNoteRangeUI		(int* iMax, int* iMin);			// get value range to display on ui;
	int getNoteShowUI		(vector<noteVector>* notes);	// get all the notes array to show for ui.
	int getNoteOrginal		(vector<noteVector>* notes);	// get all the notes array, not changed at all.

	// for matching calculation.
	int getNoteMatch		(int* pNote, int iNum);			// get note to match array by specified length;
	int getNoteCurrent		(int time_ms);					// get note value in the time input, not used now;
	int noteMatch2Ui		(int iMatch );					// convert matching note to ui note.

	int getNoteFrameNum		( );							// return note frame number; 

	int getKey();											// return the key according to the notes
	static const char* KeyToString(int key);						// Represent the key to a string

	// suggestion: 0~1; existance:0~100; at least 12 elements' capacity
	// return: 0~11 in researching mode as suggested key, KEY_IN_SUGGESTION as normal result; -1, undetermined key; -2, error   
	int statKey(int* suggestion, int* existance = NULL);

private:
	int getFileInfo			(char* noteMemory, int memSize);// get note info by memory block.
	int normalizeNote		( );							// normalize note info

private:
	int m_frame_ms;			// frame in ms
	int m_frame_num;		// frame number;
	int* m_note_to_match;	// note array to match in frame.
	int m_file_line_num;	// note file line number;
//	int m_keymode_play;		// key mode to play;
	int m_note_org_max;		// note max value orginal;
	int m_note_org_min;		// note min value orginal;

	vector<noteVector>m_note_vector_ui;	// note array to show for ui;
	vector<noteVector>m_note_vector_orginal;// note array not changed, raw data.

};



#endif

