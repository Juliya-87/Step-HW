#include "FileCell.h"

FileCell::FileCell(const MyString& value) : mValue(value)
{
}

FileCell::FileCell(MyString&& value) : mValue(std::move(value))
{
}

const MyString& FileCell::GetValue() const
{
	return mValue;
}
