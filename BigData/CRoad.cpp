#include "CRoad.h"
#include <vector>
#include <map>
#include <cstring>


std::string CRoad::m_dumpFilePath = std::string("./");

CRoad::CRoad(ENVIRONMENT env) :
	m_environment(env) {
		m_trainedDays = new std::vector<Date_t>();
		for(int i = 0; i < ROAD_MAP_ARR_SIZE; i++) {
			map_arr[i] = new std::map<RoadID_t,CRoadSegment*>();
		}
}

CRoad::CRoad(const CRoad &clone) {
	m_environment = clone.m_environment;
	/**
	调用Vector的复制构造函数，直接把vector复制过来
	*/
	m_trainedDays = new std::vector<Date_t>(*(clone.m_trainedDays));

	for(int i = 0; i < ROAD_MAP_ARR_SIZE; i++) {
		for(std::map<RoadID_t,CRoadSegment*>::iterator it =
			clone.map_arr[i]->begin();it != clone.map_arr[i]->end();it++){
				/**
				调用map的复制构造函数，因为map中的velue键值只是指针，所以直接把指针复制过来
				*/
				map_arr[i] = new std::map<RoadID_t,CRoadSegment*>(*(clone.map_arr[i]));

				/*
				map_arr[i] = new std::map<RoadID_t,CRoadSegment*>();
				map_arr[i]-> insert(
					std::pair<RoadID_t,CRoadSegment*>(it->first,it->second));
					*/
		}
	}
}

CRoad::~CRoad() {
	delete m_trainedDays;
	for(int i = 0; i < ROAD_MAP_ARR_SIZE; i++) {
		for(std::map<RoadID_t,CRoadSegment*>::iterator it =
			map_arr[i]->begin();it != map_arr[i]->end();it++){
				delete it->second;
		}
		map_arr[i]->clear();
		delete map_arr[i];
		map_arr[i] = 0;
	}
}

void CRoad::setDumpFilePath(std::string path) {
	m_dumpFilePath = path;
}

std::string CRoad::getDumpFilePath() {
	return m_dumpFilePath;
}

bool CRoad::dump() {
	const char *env[4] = {
		"weekday_good_weather",
		"weenends_good_weather",
		"weekday_bad_whether",
		"weekends_bad_whether"
	};
	if (m_trainedDays->size() <= 0) {
		LOG_INFO("-CRoad in environment:%s is empty.\n",
			env[m_environment]);
		return false;
	}

	LOG_INFO("-dump file in environment:%s\n", env[m_environment]);

	Count_t daysNum = static_cast<Count_t>(m_trainedDays->size());
	LOG_INFO("-daysNum %d\n", daysNum);
	Date_t *days = new Date_t[daysNum];
	std::vector<Date_t>::iterator it;
	int i = 0;
	for (it = m_trainedDays->begin();
		it != m_trainedDays->end(); ++it) {
		days[i++] = *it;
	}
	char fileName[128];
	sprintf(fileName,
		"%s%d_result_%s-%04d_%02d_%02d...%04d_%02d-%02d.resd",
		m_dumpFilePath.c_str() ,
		static_cast<int>(m_environment),
		env[m_environment],
		days[0].year, days[0].month, days[0].day,
		days[daysNum-1].year,
		days[daysNum-1].month,
		days[daysNum-1].day
		);
	FILE *fileHandle = fopen(fileName, "wb");
	if (fileHandle == 0) {
		LOG_ERR("Can't open file:%s!\n", fileName);
		delete[] days;
		return false;
	}
	LOG_INFO("-write result file:%s\n", fileName);
	Count_t envInCount = static_cast<Count_t>(m_environment);
	ResultFileHeader_t fHeader;

	fHeader.magic.a = HEADER_MAGIC.a;
	fHeader.magic.b = HEADER_MAGIC.b;
	fHeader.magic.c = HEADER_MAGIC.c;
	fHeader.magic.d = HEADER_MAGIC.d;

	fHeader.envir = static_cast<Count_t>(m_environment);
	fHeader.daysNum = daysNum;
	fwrite(&fHeader, sizeof(fHeader), 1, fileHandle);
	fwrite(days, sizeof(Date_t), daysNum, fileHandle);
	ResultFileRecord_t rec;
	for (int i = 0; i < ROAD_MAP_ARR_MASK; ++i) {
		std::map<RoadID_t, CRoadSegment*> *oneMap;
		oneMap = map_arr[i];
		std::map<RoadID_t, CRoadSegment*>::iterator it;
		for (it = oneMap->begin(); it != oneMap->end(); ++it) {
			//FIXME
			//没有是用缓冲区可能导致效率低下
			rec.roadId = it->first;
			const CTimeSlot * timeSlotSequence =
				it->second->getTimeSequence();
			for (int i = 0; i < TIME_SLOTS_PER_DAY; ++i) {
				rec.timeSlots[i] = timeSlotSequence[i].m_CTaxiNum;
			}
			fwrite(&rec, sizeof(rec), 1, fileHandle);
		}
	}
	fclose(fileHandle);
	delete[] days;
	return true;
}


bool CRoad::loadFromFile(std::string file) {
	FILE *fileHandle = fopen(file.c_str(), "rb");
	if (fileHandle == 0) {
		LOG_ERR("Can't load file:%s.\n", file.c_str());
		return false;
	} else {
		LOG_INFO("-Loading File:%s.\n", file.c_str());
	}

	ResultFileHeader_t fHeader;
	fread(&fHeader, sizeof(fHeader), 1, fileHandle);
	m_environment = static_cast<ENVIRONMENT>(fHeader.envir);
	Count_t daysNum = fHeader.daysNum;

	Date_t *days = new Date_t[daysNum];
	fread(days, sizeof(Date_t), daysNum, fileHandle);
	for (int i = 0; i < daysNum; ++i) {
		addTrainedDay(days[i]);
	}

	const int bufferSize = 128;
	ResultFileRecord_t record[bufferSize];
	int readCount;
	while ((readCount =
		static_cast<Count_t>(fread(record,
		sizeof(ResultFileRecord_t),
		bufferSize,
		fileHandle))) > 0) {

		///////////////////
		for (int i = 0; i < readCount; ++i) {
			CRoadSegment *rSeg;
			if (!getRoadSegment(record[i].roadId, rSeg)) {
				rSeg = new CRoadSegment(record[i].roadId);
				setRoadSegment(record[i].roadId, rSeg);
			}
			rSeg->setTimeSequence(record[i].timeSlots);
		}
	}
	fclose(fileHandle);
	return true;
}

void CRoad::addTrainedDay(Date_t &date) {
	for (std::vector<Date_t>::iterator it = m_trainedDays->begin();
		it != m_trainedDays->end(); it++) {
		if (it->day == date.day && it->month == date.month) {
			//date already existed
			return;
		}
	}
	m_trainedDays->push_back(date);
}


int CRoad::getTrainedDaysNum() {
	return static_cast<int>(m_trainedDays->size());
}

const std::vector<Date_t>* CRoad::getTrainedDays() {
	//return a copy of m_trainedDays
	return m_trainedDays;
}

void CRoad::setRoadSegment(RoadID_t &roadSegmentID,
					CRoadSegment *roadSegment) {
						/*
	map_arr[roadSegmentID & ROAD_MAP_ARR_MASK]->insert(
		std::pair<RoadID_t,CRoadSegment*>(roadSegmentID,roadSegment));
		*/
	(*map_arr[getMapArrIndex(roadSegmentID)])[roadSegmentID] =
		roadSegment;
}

bool CRoad::getRoadSegment(RoadID_t &roadSegmentID,
						   CRoadSegment* &out) {
	std::map<RoadID_t,CRoadSegment*>::iterator it;
	it = map_arr[getMapArrIndex(roadSegmentID)]->find(roadSegmentID);

	if(it == map_arr[getMapArrIndex(roadSegmentID)]->end()) {
		out = 0;
		return false;
	} else {
		out = it->second;
		return true;
	}
}


//FIXME
//XXX
double CRoad::getLambda(RoadID_t roadId,TimeSlotIndex_t index) {

	return 0.0;
}