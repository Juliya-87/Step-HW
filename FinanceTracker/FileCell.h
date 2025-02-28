#pragma once
#include "MyString.h"

class FileCell
{
private:
	MyString mValue;

public:
	FileCell(const MyString& value);
	FileCell(MyString&& value);

	const MyString& GetValue() const;
};

