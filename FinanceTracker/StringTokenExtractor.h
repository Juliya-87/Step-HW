#pragma once
#include "MyString.h"

class StringTokenExtractor
{
private:
	const char* mCurrPos;
	char mDelimiter;

public:
	StringTokenExtractor(const MyString& str, const char delimiter);

	void GetNextToken(MyString& token);
	MyString GetRemaining();
};

