#include "TimeHelper.h"

using namespace std;

time_t NormalizeTime(tm& timeInfo)
{
	while (timeInfo.tm_mon < 0)
	{
		timeInfo.tm_mon += 12;
		timeInfo.tm_year -= 1;
	}

	while (timeInfo.tm_mon > 11)
	{
		timeInfo.tm_mon -= 12;
		timeInfo.tm_year += 1;
	}

	return mktime(&timeInfo);
}

time_t AddDays(const time_t& time, const int days)
{
	return time + (static_cast<long long>(days) * 86400); // 86400 seconds in a day
}

time_t AddMonths(const time_t& time, const int months)
{
	tm timeInfo;
	(void)localtime_s(&timeInfo, &time);
	timeInfo.tm_mon += months;
	return NormalizeTime(timeInfo);
}
