#include "Counter.h"

#include "ConversionHelpers.h"

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

std::unordered_map<MyString, MyString> Counter::ToMap() const
{
	return { {"Name", mName}, {"Value", ToString(mValue)} };
}

void Counter::FromMap(const std::unordered_map<MyString, MyString>& data)
{
	mName = data.at("Name");
	mValue = StrToInt(data.at("Value"));
}

bool Counter::operator==(const Counter& other) const
{
	return mName == other.mName;
}
