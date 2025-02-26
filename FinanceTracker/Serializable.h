#pragma once
#include "MyString.h"

class Serializable
{
protected:
	Serializable() = default;

public:
	static constexpr char DELIMITER = '\t';

	virtual void Parse(MyString& str) = 0;
	virtual MyString ToString() const = 0;

	virtual ~Serializable() = default;
};

