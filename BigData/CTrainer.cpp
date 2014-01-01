#include "CTrainer.h"
#include "CRoadSegment.h"
#include "CTimeSlot.h"
#include <map>

//DEBUG
#include <iostream>



CTrainer::CTrainer() {
	m_midFileHandler = 0;
	m_road[WEEKDAY_GOOD_WEATHER] = new CRoad(WEEKDAY_GOOD_WEATHER);
	m_road[WEEKDAY_BAD_WHETHER] = new CRoad(WEEKDAY_BAD_WHETHER);
	m_road[WEEKENDS_GOOD_WEATHER] = new CRoad(WEEKENDS_GOOD_WEATHER);
	m_road[WEEKENDS_BAD_WHETHER] = new CRoad(WEEKENDS_BAD_WHETHER);
	m_daysToBeTrained = new vector<Date_t>();
	m_resultFilesToBeMerged = new vector<string>();
	Date_t tmp = {0,0,0};
	m_currentDate = tmp;
	m_currentEnv = WEEKDAY_GOOD_WEATHER;
}

CTrainer::CTrainer(const CTrainer &clone) {
	m_midFileHandler = new CMidFileHandler(*(clone.m_midFileHandler));
	m_daysToBeTrained = new vector<Date_t>(*(clone.m_daysToBeTrained));

	m_road[WEEKDAY_GOOD_WEATHER] =
		new CRoad(*(clone.m_road[WEEKDAY_GOOD_WEATHER]));
	m_road[WEEKDAY_BAD_WHETHER] =
		new CRoad(*(clone.m_road[WEEKDAY_BAD_WHETHER]));
	m_road[WEEKENDS_GOOD_WEATHER] =
		new CRoad(*(clone.m_road[WEEKENDS_GOOD_WEATHER]));
	m_road[WEEKENDS_BAD_WHETHER] =
		new CRoad(*(clone.m_road[WEEKENDS_BAD_WHETHER]));
	
	m_currentDate = clone.m_currentDate;
	m_currentEnv = clone.m_currentEnv;
}

CTrainer::~CTrainer() {
	delete m_midFileHandler;
	delete m_daysToBeTrained;
	delete m_resultFilesToBeMerged;

	delete m_road[WEEKDAY_GOOD_WEATHER];
	delete m_road[WEEKDAY_BAD_WHETHER];
	delete m_road[WEEKENDS_GOOD_WEATHER];
	delete m_road[WEEKENDS_BAD_WHETHER];

	/*
	//new festure in C++ 11
	for(CRoad *r : m_road) {
		delete r;
	}
	*/
}


void  CTrainer::setDumpFilePath(string dumpFilePath) {
	CRoad::setDumpFilePath(dumpFilePath);
}
string CTrainer::getDumpFilePath() {
	return CRoad::getDumpFilePath();
}

bool CTrainer::setPreDataPath(string path) {
	CMidFileHandler::setDataPath(path);
	return true;
}

bool CTrainer::addDayToBeTrained(Date_t day) {
	
	vector<Date_t>::iterator it;
	for(it = m_daysToBeTrained->begin();
		it != m_daysToBeTrained->end();++it) {
			if(it->day == day.day && it->month == day.month) {
				return false;
			}
	}
	m_daysToBeTrained->push_back(day);
	return true;
}

bool CTrainer::getDaysToBeTrained(vector<Date_t>* &out) {
	out =  m_daysToBeTrained;
	if(m_daysToBeTrained->size() > 0)
		return true;
	return false;
}

void  CTrainer::addResultFileToBeMerged(string resultFile) {
	vector<string>::iterator it;
	for (it = m_resultFilesToBeMerged->begin();
		it != m_resultFilesToBeMerged->end();
		++it) {
		if (*it == resultFile)
			return;
	}
	m_resultFilesToBeMerged->push_back(resultFile);
}

const vector<string>*  CTrainer::getResultFilesToBeMerged() {
	return m_resultFilesToBeMerged;
}

bool  CTrainer::dumpData() {
#if 0
	using namespace std;
	auto  showTimeSequence = [](const CTimeSlot *arr) {
		for(int i = 0; i < TIME_SLOTS_PER_DAY; i++) {
			cout << arr[i].m_CTaxiNum << " ";
		}
		cout << "]" <<  endl;
	};

	for(int i = 0; i < 4;i++) {
		CRoad *road = m_road[i];
		cout <<"ENV Type:" << i << endl;
		for(int j = 0; j < ROAD_MAP_ARR_SIZE; j++) {
			std::map<RoadID_t,CRoadSegment*>::iterator it;
			std::map<RoadID_t,CRoadSegment*> *map = 
				road->map_arr[j];
			for(it = map->begin();it != map->end(); ++it) {
				cout << "RoadID:" << it->first << "[" << endl;
				showTimeSequence(it->second->getTimeSequence());
			}
		}
	}
#endif
#if 1
	m_road[WEEKDAY_GOOD_WEATHER]->dump();
	m_road[WEEKDAY_BAD_WHETHER]->dump();
	m_road[WEEKENDS_GOOD_WEATHER]->dump();
	m_road[WEEKENDS_BAD_WHETHER]->dump();
#endif
	return true;
}

bool  CTrainer::startMerge() {
	vector<string>::iterator it;
	for (it = m_resultFilesToBeMerged->begin();
		it != m_resultFilesToBeMerged->end();
		++it){
		FILE *fileHandle = fopen(it->c_str(),"rb");
		if (fileHandle == 0) {
			LOG_ERR("Can't open file:%s\n", it->c_str());
			continue;
		}
		ResultFileHeader_t fHeader;
		fread(&fHeader, sizeof(fHeader), 1, fileHandle);
		if (fHeader.magic.a == HEADER_MAGIC.a &&
			fHeader.magic.b == HEADER_MAGIC.b &&
			fHeader.magic.c == HEADER_MAGIC.c &&
			fHeader.magic.d == HEADER_MAGIC.d ) {
			if (fHeader.envir >= 0 && fHeader.envir <= 3) {
				LOG_INFO("-loading file:%s\n", *it);
				m_road[fHeader.envir]->loadFromFile(it->c_str());
			}
			else
			{
				LOG_ERR("File environment(%d) not proper.\n",
					fHeader.envir);
			}
		}
		else
		{
			LOG_ERR("File magicNumber not match!\n\t file name:%s\n",
				it->c_str());
		}
		
	}
	return true;
}


bool  CTrainer::start() {
	if(check() != 0)
		return false;
	if(startMerge()) {
		while(m_daysToBeTrained->size() > 0) {
			if(!trainOneDay())
				return false;
		}
		if(!dumpData())
			return false;
		return true;
	}else {
		return false;
	}
}

bool CTrainer::trainOneDay() {
	m_currentDate = m_daysToBeTrained->front();
	LOG_INFO("-Train day : %d-%d-%d\n",
		m_currentDate.year,
		m_currentDate.month,
		m_currentDate.day);
	m_currentEnv = CHelper::getWeatherAndHoliday(m_currentDate);
	m_daysToBeTrained->erase(m_daysToBeTrained->begin());
	m_midFileHandler = new CMidFileHandler(m_currentDate);
	if (m_midFileHandler->openFile()) {
		m_road[m_currentEnv]->addTrainedDay(m_currentDate);
		Record_t record;
		while (m_midFileHandler->getRecord(record)) {
			/*
			std::cout << "RCD: " << record.roadId
			<< " " << record.index << std::endl;
			*/
			trainOneRecord(record.roadId, record.index, m_currentEnv);
		}
	}
	delete m_midFileHandler;
	m_midFileHandler = 0;
	return true;
}

bool CTrainer::trainOneRecord(RoadID_t rId,
							  TimeSlotIndex_t index,
							  ENVIRONMENT env) {
	CRoadSegment *rSeg;
	if(!m_road[env]->getRoadSegment(rId,rSeg)) {
		rSeg = 	new CRoadSegment(rId);
		m_road[env]->setRoadSegment(rId, rSeg);
	}

	CTimeSlot *timeSlot;
	if(rSeg->getTimeSlot(index, timeSlot)) {
		timeSlot->m_CTaxiNum++;
		return true;
	}
	return false;
}

int CTrainer::check() {

	return 0;
}
