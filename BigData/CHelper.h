#pragma once

#include "Types.h"


class CHelper {
public:
	static RoadID_t getRoadID(GPSCoor_t longitude,
		GPSCoor_t latitude);

	static ENVIRONMENT getWeatherAndHoliday(Date_t time);
};
