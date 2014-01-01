#include "CRoadSegment.h"
#include "CTimeSlot.h"

CRoadSegment::CRoadSegment(RoadID_t roadId) :
	m_roadId(roadId) {
		m_TimeSequence = new CTimeSlot[TIME_SLOTS_PER_DAY];
		for (int i = 0; i < TIME_SLOTS_PER_DAY; ++i) {
			m_TimeSequence[i].m_CTaxiNum = 0;
		}
}

CRoadSegment::CRoadSegment(const CRoadSegment &clone) {
	m_roadId = clone.m_roadId;
	m_TimeSequence = new CTimeSlot[TIME_SLOTS_PER_DAY];
	//
	for(int i = 0; i < TIME_SLOTS_PER_DAY;i++) {
		m_TimeSequence[i].m_CTaxiNum = clone.m_TimeSequence[i].m_CTaxiNum;
	}
}

CRoadSegment::~CRoadSegment() {
	delete[] m_TimeSequence;
}

int CRoadSegment::getCover(TimeSlotIndex_t index,
						   TimeSlotIndex_t &out_start,
						   TimeSlotIndex_t &out_end) {
	if((out_start = index - COVER_LEN_BACKWORD) < 0)
		out_start = 0;
	if((out_end = index + COVER_LEN_FORWORD) >= TIME_SLOTS_PER_DAY)
		out_end = TIME_SLOTS_PER_DAY -1;
	return out_end - out_start + 1;
}

double CRoadSegment::getCompletionRate() {
	int filled = 0;
	for(int i = 0; i < TIME_SLOTS_PER_DAY; i++) {
		if(m_TimeSequence[i].m_CTaxiNum != 0) {
			filled++;
		}
	}
		return (double)filled / TIME_SLOTS_PER_DAY;
}