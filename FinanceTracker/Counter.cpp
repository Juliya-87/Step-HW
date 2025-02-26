#include "Counter.h"

#include <cstdlib>

#include "StringTokenExtractor.h"

void Counter::Parse(MyString& str)
{
	StringTokenExtractor splitter(str, DELIMITER);
	MyString token;
	char* endPtr = nullptr;

	splitter.GetNextToken(token);
	mName = token;

	splitter.GetNextToken(token);
	mValue = strtol(token.GetCStr(), &endPtr, 10);

	str = splitter.GetRemaining();
}

MyString Counter::ToString() const
{
	MyString str;
	str.Append(mName);
	str.Append(DELIMITER);
	str.Append(mValue);
	return str;
}

Counter::Counter(const MyString& name) : mName(name)
{
	mValue = 0;
}

int Counter::GetNextValue()
{
	mValue++;
	return mValue;
}

const MyString& Counter::GetName() const
{
	return mName;
}

bool Counter::operator==(const Counter& other) const
{
	return mName == other.mName;
}
