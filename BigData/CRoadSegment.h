#pragma once

#include "Types.h"
#include "CTimeSlot.h"

class Trainer;

class CRoadSegment {
private:

	RoadID_t m_roadId;
	/**
	在构造函数中 m_TimeSequence = new CTimeSlot[TIME_SLOTS_PER_DAY]；
	在析构函数中delete
	*/
	CTimeSlot *m_TimeSequence; //[TIME_SLOTS_PER_DAY];

	/*
	定义友元类
	*/
	//friend CTrainer;
public:
	CRoadSegment(RoadID_t roadId);
	CRoadSegment(const CRoadSegment &clone);//copy
	virtual ~CRoadSegment();

	virtual const CTimeSlot* getTimeSequence();

	virtual bool getTimeSlot(TimeSlotIndex_t index, CTimeSlot* &out);

	virtual bool setTimeSequence(const Count_t *from);
	/**
	获取覆盖，成功返回长度，失败了返回值为-1
	*/
	virtual int getCover(TimeSlotIndex_t index, TimeSlotIndex_t &out_start, TimeSlotIndex_t &out_end);
	/**
	计算数据完整率
	*/
	virtual double getCompletionRate();
};
inline bool CRoadSegment::setTimeSequence(const Count_t *from) {
	for (int i = 0; i < TIME_SLOTS_PER_DAY; ++i) {
		m_TimeSequence[i].m_CTaxiNum =  from[i];
	}
	return true;
}
inline const CTimeSlot* CRoadSegment::getTimeSequence() {
	return m_TimeSequence;
}

inline bool CRoadSegment::getTimeSlot(TimeSlotIndex_t index, CTimeSlot* &out) {
	if(index >= 0 && index < TIME_SLOTS_PER_DAY) {
		out = &m_TimeSequence[index];
		return true;
	} 
	out = 0;
	return false;
}