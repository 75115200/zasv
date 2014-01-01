#pragma once

#include <iostream>
#include <vector>
#include "Types.h"
#include "CMidFileHandler.h"
#include "CTimeSlot.h"
#include "CRoad.h"
#include "CHelper.h"

using std::vector;
using std::string;

/**
CTrainer��������ѵ�����̿����࣬�������̵ĵ���
*/
class CTrainer {
private:
	CMidFileHandler *m_midFileHandler;
	CRoad *m_road[ENV_NUM];
	vector<Date_t> *m_daysToBeTrained;
	vector<string> *m_resultFilesToBeMerged;
	Date_t m_currentDate;
	ENVIRONMENT m_currentEnv;

	/**
	��ʼ�ϲ��趨(resultsToBeMerged)�ļ�������
	*/
	virtual bool startMerge();
	virtual bool trainOneDay();
	virtual bool trainOneRecord(RoadID_t rId,
		TimeSlotIndex_t index,ENVIRONMENT env);
public:
	CTrainer();
	CTrainer(const CTrainer &clone);
	virtual ~CTrainer();

	static void setDumpFilePath(string dumpFileName);
	static string getDumpFilePath();

	virtual bool setPreDataPath(string path);
	virtual bool addDayToBeTrained(Date_t day);
	virtual bool getDaysToBeTrained(vector<Date_t>* &out);

	virtual void addResultFileToBeMerged(string resultFile);
	virtual const vector<string>* getResultFilesToBeMerged();

	/**
	��ѵ�����ݱ��浽�����ϣ�������������R��
	*/
	virtual bool dumpData();

	/**
	���ȵ���startMerge��������resultFiles��Ȼ��ʼ��ȡrecords
	����ѵ����ѵ����ɺ����dumpData��������
	��ʼѵ���趨������(daysToBETrained)������
	*/
	virtual bool start();

	/**
	���������Ϣ�Ƿ��Ѿ����趨��
	*/
	virtual int check();
};