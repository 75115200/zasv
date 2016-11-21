#ifndef C_SECTION_CFG_H_H
#define C_SECTION_CFG_H_H

/************************************************************************/
/* 分段合唱的cfg文件生成和读写。				                    */
/* written by ethanzhao, modified Feb.28,2015.                          */
/************************************************************************/

#include "MSdcommon.h"
#include <vector>
#include <string>
#include "SectionInfo.h"
#include "CqrcSection2.h"
#include "CqrcStar2.h"
#include "KalaInterfaces.h"

using namespace std;

/*
* get section cfg info class
*/
class LIB_KALAAUDIOBASE_API CSectionUser:public IKalaSection
{
public:

	/* overload function, input section file name & sentence info, like score. */
	int init( char* section_file_name, vector<int>sentences);

	/* overload function, input section file memory & sentence info, like score. */
	int init( char* section_memory, int input_len, vector<int>sentences); // input memory not file.
	
	/* get section info all. get every sentence's section info. sentence,0,1,2,3...*/
	int GetSectionInfo	(vector<SectionSingers>* section_info_all);	

	/* uninit function*/
	void uinit ( );	

private:

private:
	vector<SectionSingers>	m_section_all;	// section info
	string m_cfg_file_name;					// cfg file name.
	
};



class CSectionCfgServer
{
public:
	int init( char* qrc_file);		// input qrc file and output cfg file.
	void uinit ( );

	//int WriteCfg (char* cfg_name );

	int OutSectionBuffer	(string* out_buffer);		// output section info as buffer;
	int OutSectionFile		(char* section_file_name);	// output section info as file.

private:

	CqrcStar2 m_qrc_star;
	CqrcSection2 m_qrc_section;

	vector<SectionSingers> m_section_A;
	vector<SectionSingers> m_section_B;
	vector<SectionSingers> m_section_C;
	vector<SectionSingers> m_section_all;

};






#endif
