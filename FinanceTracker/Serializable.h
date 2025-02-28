#pragma once
#include <unordered_map>

#include "MyString.h"

class Serializable
{
protected:
	Serializable() = default;

public:
	virtual std::unordered_map<MyString, MyString> ToMap() const = 0;
	virtual void FromMap(const std::unordered_map<MyString, MyString>& data) = 0;

	Serializable& operator=(const Serializable& other) = default;

	virtual ~Serializable() = default;
};

