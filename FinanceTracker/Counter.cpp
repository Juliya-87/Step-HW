#include "Counter.h"

#include <cstdlib>
#include <cstring>

void Counter::Parse(MyString& str)
{
	char* chars = str.GetCStr();
	char* context = nullptr;
	char* endPtr = nullptr;

	char* token = strtok_s(chars, DELIMITER, &context);
	mName = MyString(token);

	token = strtok_s(nullptr, DELIMITER, &context);
	mValue = strtol(token, &endPtr, 10);

	str = MyString(context);
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
