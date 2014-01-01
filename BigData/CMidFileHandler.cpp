#include <iostream>
#include <cstdio>
#include <cstring>
#include "CMidFileHandler.h"

using std::string;
string CMidFileHandler::m_dataPath = string("./");

CMidFileHandler::CMidFileHandler(Date_t date) :
m_dayToBeTrained(date), m_currentTimeSlotIndex(0)
{
	m_fileHandle = 0;
	m_records = new vector<Record_t>();
	m_midFileHeader = 0;
	m_dayFilesToBeLoaded = new vector<string>();
	m_memmap_start = 0;
	m_memmap_cur = 0;
	m_memmap_end = 0;

	char fileName[32];
	sprintf(fileName, "%s%4d%02d%02d.dat",
		m_dataPath.c_str(),
		m_dayToBeTrained.year,
		m_dayToBeTrained.month,
		m_dayToBeTrained.day);
	m_dayFilesToBeLoaded->push_back(string(fileName));
}

CMidFileHandler::CMidFileHandler(const CMidFileHandler &clone) {
	m_fileHandle = 0;
	m_records = new std::vector<Record_t>(*clone.m_records);
	m_midFileHeader = 0;
	m_dayFilesToBeLoaded =
		new std::vector<string>(*clone.m_dayFilesToBeLoaded);
	m_currentTimeSlotIndex = clone.m_currentTimeSlotIndex;

}

CMidFileHandler::~CMidFileHandler() {
	if (m_fileHandle != 0)
		fclose(m_fileHandle);
	delete m_records;
	delete m_midFileHeader;
}

void CMidFileHandler::setDataPath(string path) {
	m_dataPath = path;
}

string CMidFileHandler::getDataPath() {
	return m_dataPath;
}

bool CMidFileHandler::openFile() {
	m_fileHandle = 0;
	string fileName;
	while (m_fileHandle == 0 &&
		m_dayFilesToBeLoaded->size() != 0) {
		fileName = m_dayFilesToBeLoaded->front();
		m_fileHandle = fopen(fileName.c_str(), "rb");
		m_dayFilesToBeLoaded->erase(m_dayFilesToBeLoaded->begin());

		if (m_fileHandle == 0)
			LOG_ERR("Open file failed:%s\n", fileName.c_str());
	}

	if (m_fileHandle == 0){
		LOG_INFO("\n");
		return false;
	} else {
		LOG_INFO("-train data in file %s\n", fileName.c_str());
	}
	return true;
}

int CMidFileHandler::loadRecords(int count) {
	if (count <= 0)
		return 0;
	if (m_fileHandle == 0 && !openFile())
		return 0;
	int readNumber = 0;
	if (m_memmap_start == 0) {
		//read whole file into memory
		fseek(m_fileHandle, 0, SEEK_END);
		std::size_t fileSize = ftell(m_fileHandle);
		fseek(m_fileHandle, 0, SEEK_SET);
		m_memmap_start = new char[fileSize];
		fread(m_memmap_start, sizeof(char), fileSize, m_fileHandle);
		m_memmap_cur = m_memmap_start;
		m_memmap_end = m_memmap_start + fileSize;
		
		U32 index;
		memcpy(&index, m_memmap_cur, sizeof(U32));
		m_memmap_cur += sizeof(U32);
		m_currentTimeSlotIndex = static_cast<TimeSlotIndex_t>(index);
		LOG_INFO("-progress percentage:00%%");
	}

	while (readNumber < count && m_memmap_cur < m_memmap_end) {
		U32 record;
		memcpy(&record, m_memmap_cur, sizeof(U32));
		m_memmap_cur += sizeof(U32);
		if (record != 0) {
			Record_t r = {
				static_cast<RoadID_t>(record),
				m_currentTimeSlotIndex
			};
			m_records->push_back(r);
			readNumber++;
		}
		else {
			U32 data;
			data = *((U32*)m_memmap_cur);
			memcpy(&data, m_memmap_cur, sizeof(U32));
			m_memmap_cur += sizeof(U32);
			if((m_currentTimeSlotIndex + 1) % 4 == 0)
				LOG_INFO("\b\b\b%02d%%",
				(m_currentTimeSlotIndex + 1) * 100 / 480);
			/*
			LOG_INFO("-count in TS:%d is %d.\n",
				m_currentTimeSlotIndex,
				static_cast<int>(data));
				*/
			memcpy(&data, m_memmap_cur, sizeof(U32));
			m_memmap_cur += sizeof(U32);
			m_currentTimeSlotIndex = static_cast<TimeSlotIndex_t>(data);
		}
	}
	if (m_memmap_cur >= m_memmap_end) {
		fclose(m_fileHandle);
		delete[] m_memmap_start;
		m_fileHandle = 0;
		m_memmap_cur = 0;
		m_memmap_start = 0;
		m_memmap_end = 0;
	}
		return readNumber;
}

bool CMidFileHandler::getDaysToBeLoaded(vector<string>* &out) {

	return true;
}

bool CMidFileHandler::getRecord(Record_t &out) {
	//if (m_fileHandle == 0 && !openFile())
	//	return false;
	if (m_records->size() == 0 && loadRecords(1024) == 0) {
		return false;
	}

	out = m_records->front();
	m_records->erase(m_records->begin());
	return true;
}