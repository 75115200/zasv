#pragma once

//#ifdef _DEBUG
#include <cstdio>
#define LOG_INFO(format, ...) fprintf(stdout, format, ##__VA_ARGS__)
#define LOG_ERR(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
//#else
//#define LOG_INFO(format, ...) do{}while(0)
//#define LOG_ERR(format, ...) do{}while(0)
//#endif

//时间粒度 默认三分钟
#define TIME_SLOT_GRAN 3
#define TIME_SLOTS_PER_DAY (24*60/TIME_SLOT_GRAN)
#define COVER_LEN_FORWORD 3
#define COVER_LEN_BACKWORD 3

/**
MASK = 0111_1111 = 0x7f = 127
*/
#define ROAD_MAP_ARR_MASK 0x7f

#define ROAD_MAP_ARR_SIZE (ROAD_MAP_ARR_MASK + 1)

typedef unsigned int RoadID_t;
typedef int Count_t;

typedef int TimeSlotIndex_t;
typedef int TaxiID_t;
typedef unsigned int TriggerEvent_t;
typedef unsigned int TaxiStatue_t;

typedef struct {
	short year;
	char month;
	char day;
} Date_t,*Date_Pt;
	
typedef struct {
	char hour;
	char minute;
	char second;
} Time_t,*Time_Pt;

typedef double GPSCoor_t;
typedef unsigned int Angle_t;

/**
*/
typedef struct {
	RoadID_t roadId;
	TimeSlotIndex_t index;
} Record_t,*Record_Pt;

#ifdef _PLATFORM_OS_LINUX
typedef uint32_t U32;
#else
typedef unsigned __int32 U32;
#endif

typedef struct {

} MidFileHeader_t;

typedef struct {
	RoadID_t roadId;
} MidFileRecord_t;

typedef struct {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
} MagicNum_t;

const MagicNum_t HEADER_MAGIC = {
	0x2,0x1,0x4,0x3
	//0xa2,0xc1,0xd4,0xf3
};

typedef struct {
	MagicNum_t magic;
	Count_t envir;
	Count_t daysNum;
} ResultFileHeader_t;

typedef struct {
	RoadID_t roadId;
	Count_t timeSlots[TIME_SLOTS_PER_DAY];
} ResultFileRecord_t;


/*
ENVIRONMENT
是日期的分类情况，
可以按照weekday，weekends，好天气，坏天气，分类
*/
enum ENVIRONMENT {
	WEEKDAY_GOOD_WEATHER = 0,
	WEEKENDS_GOOD_WEATHER,
	WEEKDAY_BAD_WHETHER,
	WEEKENDS_BAD_WHETHER,
};
#define ENV_NUM 4