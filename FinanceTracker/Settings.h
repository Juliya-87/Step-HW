#pragma once
#include "MyString.h"

class Settings
{
public:
	Settings(const MyString& dataBaseDirectory, const MyString& reportsBaseDirectory);

	const MyString& GetDataBaseDirectory() const;
	const MyString& GetReportsBaseDirectory() const;

private:
	MyString mDataBaseDirectory;
	MyString mReportsBaseDirectory;
};
