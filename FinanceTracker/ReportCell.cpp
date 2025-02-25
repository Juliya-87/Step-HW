#include "ReportCell.h"

using namespace std;

ReportCell::ReportCell(const MyString& value, const streamsize width, const bool isLeftAligned) : mValue(value)
{
	mWidth = width;
	mIsLeftAligned = isLeftAligned;
}

const MyString& ReportCell::GetValue() const
{
	return mValue;
}

std::streamsize ReportCell::GetWidth() const
{
	return mWidth;
}

bool ReportCell::GetIsLeftAligned() const
{
	return mIsLeftAligned;
}
