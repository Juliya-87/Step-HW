#pragma once
#include "FileData.h"
#include "MyString.h"

class FileHandler
{
public:
	virtual ~FileHandler() = default;

	virtual MyString GetExtension() const = 0;

	virtual void SaveToFile(const MyString& fileName, const std::unique_ptr<FileData>& data) = 0;
	virtual std::unique_ptr<FileData> LoadFromFile(const MyString& fileName) = 0;
};
