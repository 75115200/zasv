#pragma once

#include <map>
#include <vector>
#include <string>
#include "CRoadSegment.h"
#include "Types.h"


class CTrainer;

class CRoad {
private:
	static std::string m_dumpFilePath;
	/**
	这张表中存放的数据所在天的情况（好天气与否，Weekdays与否
	*/
	ENVIRONMENT m_environment;

	/**
	存储这张表中目前训练了哪些天的数据
	*/
	std::vector<Date_t> *m_trainedDays;

	/**
	*/
	std::map<RoadID_t,CRoadSegment*>
		*map_arr[ROAD_MAP_ARR_SIZE];

	int getMapArrIndex(RoadID_t roadId);

	/**
	声明友元类
	*/
	friend class CTrainer;
public:
	CRoad(ENVIRONMENT env);
	CRoad(const CRoad &clone);
	virtual ~CRoad();
	
	static void setDumpFilePath(std::string path);
	static std::string getDumpFilePath(); 

	bool dump();
	bool loadFromFile(std::string fileName);

	/**
	添加一个日期，这一天训练后的的数据已经存在此表中了
	*/
	virtual void addTrainedDay(Date_t &date);
	/**
	获取共训练了的天数
	*/
	virtual int getTrainedDaysNum();
	/**
	获取trainedDays向量的一个副本
	*/
	virtual const std::vector<Date_t>* getTrainedDays();

	virtual void setEnvironment(ENVIRONMENT env);
	virtual ENVIRONMENT getEnvironment();

	/**
	给哈希表中添加路段信息
	输入：路段的ID，以及CRoadSegment类的引用
	*/
	virtual void setRoadSegment(RoadID_t &roadSegmentID,
		CRoadSegment *roadSegment);

	/**
	通过路段的ID获取路段信息（CRoadSegment）
	*/
	virtual bool getRoadSegment(RoadID_t &roadSegmentID,
		CRoadSegment* &out);

	/**
	给定路段时间点，获取该时间点的 lambda
	*/
	virtual double getLambda(RoadID_t roadId,TimeSlotIndex_t index);

};

inline int CRoad::getMapArrIndex(RoadID_t roadID) {
	return roadID & ROAD_MAP_ARR_MASK;
}

inline void CRoad::setEnvironment(ENVIRONMENT env) {
	m_environment = env;
}

inline ENVIRONMENT CRoad::getEnvironment() {
	return m_environment;
}