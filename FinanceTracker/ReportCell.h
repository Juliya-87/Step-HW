#pragma once
#include <ios>

#include "MyString.h"

class ReportCell final
{
public:
	ReportCell(const MyString& value, std::streamsize width = 0, bool isLeftAligned = true);

	const MyString& GetValue() const;
	std::streamsize GetWidth() const;
	bool GetIsLeftAligned() const;

private:
	MyString mValue;
	std::streamsize mWidth;
	bool mIsLeftAligned;
};
