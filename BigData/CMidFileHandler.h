#pragma once

#include "Types.h"
#include <vector>
#include <iostream>

using std::vector;
using std::string;

class CMidFileHandler {
private:
	/**
	�ļ����
	*/
	static string m_dataPath;
	FILE *m_fileHandle;
	vector<Record_t> *m_records;
	//vector<string>::iterator m_recordIt;
	MidFileHeader_t *m_midFileHeader;
	vector<string> *m_dayFilesToBeLoaded;
	Date_t m_dayToBeTrained;
	TimeSlotIndex_t m_currentTimeSlotIndex;
	char *m_memmap_start;
	char *m_memmap_cur;
	char *m_memmap_end;
	
	/**
	��Ԥ����֮����м��ļ�����ȡ�ļ�ͷ��m_midFileHeader,
	�����ļ�������Ƶ� m_FileHandle
	*/

	/**
	�������m_records
	����Ԥ����֮����ļ�,����count����¼��
	�洢��m_records�У�
	����ʼ�������������ؼ��ؼ�¼��Ŀ��û���ص�����0����ʾEOF,
	���ر��ļ��������m_fileHandler��ֵΪ0
	*/
	virtual int loadRecords(int count);

public:
	CMidFileHandler(Date_t);
	CMidFileHandler(const CMidFileHandler& clone);
	virtual ~CMidFileHandler();

	virtual bool openFile();
	static void setDataPath(string path);
	static string getDataPath();
	virtual bool getDaysToBeLoaded(vector<string>* &out);
	
	//���溯�����ڻ�ȡ����֮���Record
	/**
	��ȡ��һ����¼
	��������һ����¼ʱ����false��out=0
	*/
	virtual bool getRecord(Record_t &out);
};