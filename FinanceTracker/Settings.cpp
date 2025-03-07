#include "Settings.h"

Settings::Settings(const MyString& dataBaseDirectory, const MyString& reportsBaseDirectory)
	: mDataBaseDirectory(dataBaseDirectory), mReportsBaseDirectory(reportsBaseDirectory)
{
}

const MyString& Settings::GetDataBaseDirectory() const
{
	return mDataBaseDirectory;
}

const MyString& Settings::GetReportsBaseDirectory() const
{
	return mReportsBaseDirectory;
}
