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
CTrainer类是整个训练过程控制类，负责流程的调度
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
	开始合并设定(resultsToBeMerged)文件的数据
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
	把训练数据保存到磁盘上，即保存整个大R表
	*/
	virtual bool dumpData();

	/**
	首先调用startMerge方法加载resultFiles，然后开始读取records
	进行训练，训练完成后调用dumpData保存数据
	开始训练设定日期内(daysToBETrained)的数据
	*/
	virtual bool start();

	/**
	检查所需信息是否已经被设定了
	*/
	virtual int check();
};