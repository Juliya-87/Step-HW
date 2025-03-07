#include "Counter.h"

#include "ConversionHelpers.h"

using namespace std;

Counter::Counter(const MyString& name) : mName(name)
{
	mValue = 0;
}

bool Counter::operator==(const Counter& other) const
{
	return mName == other.mName;
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

unordered_map<MyString, MyString> Counter::ToMap() const
{
	return { {"Name", mName}, {"Value", ToString(mValue)} };
}

void Counter::FromMap(const unordered_map<MyString, MyString>& data)
{
	mName = data.at("Name");
	mValue = StrToInt(data.at("Value"));
}
