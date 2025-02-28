#pragma once
#include <cstdint>

#include "FileHandler.h"
#include "MyString.h"

class CsvFileHandler final : public FileHandler
{
private:
	static constexpr char FILE_EXTENSION[] = ".csv";
	static constexpr char DELIMITER = ',';

	static MyString EscapeCsvValue(const MyString& value);
	static std::unique_ptr<FileRow> ParseCsvRow(const MyString& line);

public:
	MyString GetExtension() const override;

	void SaveToFile(const MyString& fileName, const std::unique_ptr<FileData>& data) override;
	std::unique_ptr<FileData> LoadFromFile(const MyString& fileName) override;
};

