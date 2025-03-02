#include "ConversionHelpers.h"

#include <iomanip>
#include <sstream>

#include "MyString.h"

static constexpr size_t TIME_BUFFER_SIZE = 50;
static constexpr size_t DOUBLE_BUFFER_SIZE = 30;
static constexpr size_t INT_BUFFER_SIZE = 12;

MyString ToString(const time_t time, const char* format)
{
	tm timeInfo;
	char buffer[TIME_BUFFER_SIZE];

	(void)localtime_s(&timeInfo, &time);
	(void)strftime(buffer, TIME_BUFFER_SIZE, format, &timeInfo);

	return {buffer};
}

time_t StrToTime(const MyString& str, const char* format)
{
	tm timeInfo;

	std::istringstream ss(str.GetCStr());
	ss >> std::get_time(&timeInfo, format);

	return mktime(&timeInfo);
}

MyString ToString(const AccountType type)
{
	switch (type)
	{
	case CREDIT_CARD:
		return { "Credit card" };
	case DEBIT_CARD:
		return { "Debit card" };
	case WALLET:
		return { "Wallet" };
	default:
		return { "Unknown type" };
	}
}

MyString ToString(const double value, const int precision)
{
	char buffer[DOUBLE_BUFFER_SIZE];
	char format[10];
	(void)sprintf_s(format, sizeof(format), "%%.%df", precision);
	(void)sprintf_s(buffer, DOUBLE_BUFFER_SIZE, format, value);

	return { buffer };
}

double StrToDouble(const MyString& str)
{
	char* endPtr = nullptr;
	return strtod(str.GetCStr(), &endPtr);
}

MyString ToString(const int value)
{
	char buffer[INT_BUFFER_SIZE];
	_itoa_s(value, buffer, 10);

	return { buffer };
}

int StrToInt(const MyString& str)
{
	char* endPtr = nullptr;
	return strtol(str.GetCStr(), &endPtr, 10);
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

AccountType StrToAccountType(const MyString& str)
{
	return IntToAccountType(StrToInt(str));
}
