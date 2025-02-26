#pragma once
#include <cstdint>

enum ReportingPeriod : uint8_t
{
	UNDEFINED = 0,
	DAY = 1,
	WEEK = 2,
	MONTH = 3
};