#pragma once
#include <iomanip>

#include "AccountType.h"

constexpr char DEFAULT_TIME_FORMAT[] = "%Y-%m-%d %H:%M:%S";

void TimeToString(char* buffer, int bufferSize, time_t time, const char* format = DEFAULT_TIME_FORMAT);

void ParseTime(time_t& time, const char* str, const char* format = DEFAULT_TIME_FORMAT);

const char* AccountTypeToString(AccountType type);

void DoubleToString(char* buffer, int bufferSize, double value, int precision = 2);
