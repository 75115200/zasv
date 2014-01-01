#pragma once

#include "Types.h"
#include "CTimeSlot.h"

class Trainer;

class CRoadSegment {
private:

	RoadID_t m_roadId;
	/**
	�ڹ��캯���� m_TimeSequence = new CTimeSlot[TIME_SLOTS_PER_DAY]��
	������������delete
	*/
	CTimeSlot *m_TimeSequence; //[TIME_SLOTS_PER_DAY];

	/*
	������Ԫ��
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
	��ȡ���ǣ��ɹ����س��ȣ�ʧ���˷���ֵΪ-1
	*/
	virtual int getCover(TimeSlotIndex_t index, TimeSlotIndex_t &out_start, TimeSlotIndex_t &out_end);
	/**
	��������������
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