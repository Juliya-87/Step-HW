#include "ConversionHelpers.h"

#include <sstream>

void TimeToString(char* buffer, const size_t bufferSize, const time_t time, const char* format)
{
	tm timeInfo = {};

	(void)localtime_s(&timeInfo, &time);
	(void)strftime(buffer, bufferSize, format, &timeInfo);
}

void ParseTime(time_t& time, const char* str, const char* format)
{
	tm timeInfo = {};

	std::istringstream ss(str);
	ss >> std::get_time(&timeInfo, format);

	time = mktime(&timeInfo);
}

const char* AccountTypeToString(const AccountType type)
{
	switch (type)
	{
	case CREDIT_CARD:
		return "Credit card";
	case DEBIT_CARD:
		return "Debit card";
	case WALLET:
		return "Wallet";
	default:
		return "Unknown type";
	}
}

void DoubleToString(char* buffer, const size_t bufferSize, const double value, const int precision)
{
	char format[10];
	(void)sprintf_s(format, sizeof(format), "%%.%df", precision);
	(void)sprintf_s(buffer, bufferSize, format, value);
}

ReportingPeriod IntToReportingPeriod(const int value)
{
	switch (value)
	{
	case 1: return DAY;
	case 2: return WEEK;
	case 3: return MONTH;
	default: return UNDEFINED;
	}
}

AccountType IntToAccountType(const int value)
{
	switch (value)
	{
	case 1: return CREDIT_CARD;
	case 2: return DEBIT_CARD;
	case 3: return WALLET;
	default: return NONE;
	}
}
