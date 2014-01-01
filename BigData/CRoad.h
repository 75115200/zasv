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
	���ű��д�ŵ��������������������������Weekdays���
	*/
	ENVIRONMENT m_environment;

	/**
	�洢���ű���Ŀǰѵ������Щ�������
	*/
	std::vector<Date_t> *m_trainedDays;

	/**
	*/
	std::map<RoadID_t,CRoadSegment*>
		*map_arr[ROAD_MAP_ARR_SIZE];

	int getMapArrIndex(RoadID_t roadId);

	/**
	������Ԫ��
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
	���һ�����ڣ���һ��ѵ����ĵ������Ѿ����ڴ˱�����
	*/
	virtual void addTrainedDay(Date_t &date);
	/**
	��ȡ��ѵ���˵�����
	*/
	virtual int getTrainedDaysNum();
	/**
	��ȡtrainedDays������һ������
	*/
	virtual const std::vector<Date_t>* getTrainedDays();

	virtual void setEnvironment(ENVIRONMENT env);
	virtual ENVIRONMENT getEnvironment();

	/**
	����ϣ�������·����Ϣ
	���룺·�ε�ID���Լ�CRoadSegment�������
	*/
	virtual void setRoadSegment(RoadID_t &roadSegmentID,
		CRoadSegment *roadSegment);

	/**
	ͨ��·�ε�ID��ȡ·����Ϣ��CRoadSegment��
	*/
	virtual bool getRoadSegment(RoadID_t &roadSegmentID,
		CRoadSegment* &out);

	/**
	����·��ʱ��㣬��ȡ��ʱ���� lambda
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