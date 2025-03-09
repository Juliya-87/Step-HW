#pragma once

#include "AccountType.h"
#include "MyString.h"
#include "ReportingPeriod.h"

constexpr char DEFAULT_TIME_FORMAT[] = "%Y-%m-%d %H:%M:%S";

MyString ToString(time_t time, const MyString& format = DEFAULT_TIME_FORMAT);
time_t StrToTime(const MyString& str, const MyString& format = DEFAULT_TIME_FORMAT);
MyString ToString(AccountType type);
MyString ToString(double value, int precision);
double StrToDouble(const MyString& str);
MyString ToString(int value);
int StrToInt(const MyString& str);
ReportingPeriod IntToReportingPeriod(int value);
AccountType IntToAccountType(int value);
AccountType StrToAccountType(const MyString& str);
