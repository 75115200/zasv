#pragma once

#include "Types.h"
#include <vector>
#include <iostream>

using std::vector;
using std::string;

class CMidFileHandler {
private:
	/**
	文件句柄
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
	打开预处理之后的中间文件，读取文件头到m_midFileHeader,
	并把文件句柄复制到 m_FileHandle
	*/

	/**
	首先清除m_records
	加载预处理之后的文件,加载count条记录，
	存储到m_records中，
	并初始化迭代器，返回加载记录数目；没加载到返回0，表示EOF,
	并关闭文件句柄。将m_fileHandler赋值为0
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
	
	//下面函数用于获取加载之后的Record
	/**
	获取下一条记录
	不存在下一条记录时返回false，out=0
	*/
	virtual bool getRecord(Record_t &out);
};