#pragma once
#include "MyString.h"

class FileCell
{
public:
	FileCell(const MyString& value);
	FileCell(MyString&& value);

	const MyString& GetValue() const;

private:
	MyString mValue;
};
