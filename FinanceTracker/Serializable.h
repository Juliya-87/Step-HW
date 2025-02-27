#pragma once
#include <map>

#include "MyString.h"

class Serializable
{
protected:
	Serializable() = default;

public:
	virtual std::map<MyString, MyString> ToMap() const = 0;
	virtual void FromMap(const std::map<MyString, MyString>& data) = 0;

	virtual ~Serializable() = default;
};

