#include "CsvFileHandler.h"

#include <fstream>

#include "Console.h"

using namespace std;

MyString CsvFileHandler::EscapeCsvValue(const MyString& value)
{
	if (value.Contains(DELIMITER) || value.Contains('"'))
	{
		MyString escapedValue = value;
		size_t pos = 0;
		while ((pos = escapedValue.Find('"', pos)) != SIZE_MAX)
		{
			escapedValue.Insert(pos, "\"");
			pos += 2; // Skip over the inserted quote
		}

		escapedValue.Insert(0, "\"");
		escapedValue.Append("\"");
		return escapedValue;
	}

	return value;
}

unique_ptr<FileRow> CsvFileHandler::ParseCsvRow(const MyString& line)
{
	auto row = make_unique<FileRow>();
	bool insideQuotes = false;
	MyString value;

	for (size_t i = 0; i < line.GetLength(); i++)
	{
		const char ch = line[i];

		if (ch == '"')
		{
			if (insideQuotes && line[i + 1] == '"')
			{
				// Handle escaped quotes ("" -> ")
				value.Append("\"");
				i++;
			}
			else
			{
				insideQuotes = !insideQuotes;
			}
		}
		else if (ch == DELIMITER && !insideQuotes)
		{
			row->AddCell(value);
			value.Clear();
		}
		else
		{
			value.Append(1, ch);
		}
	}

	row->AddCell(std::move(value)); // Add last value
	return row;
}

MyString CsvFileHandler::GetExtension() const
{
	return { FILE_EXTENSION };
}

void CsvFileHandler::SaveToFile(const MyString& fileName, const unique_ptr<FileData>& data)
{
	ofstream file(fileName.GetCStr());
	if (!file.is_open())
	{
		Console::WriteLine("Unable to open the file ", fileName);
		return;
	}

	if (data->IsEmpty())
	{
		file.close();
		return;
	}

	for (const auto& row : data->GetRows())
	{
		bool isFirstCell = true;
		for (const auto& cell : row->GetCells())
		{
			if (!isFirstCell)
			{
				file << DELIMITER;
			}

			file << EscapeCsvValue(cell->GetValue());
			isFirstCell = false;
		}

		file << "\n";
	}

	file.close();
}

unique_ptr<FileData> CsvFileHandler::LoadFromFile(const MyString& fileName)
{
	auto data = make_unique<FileData>();

	ifstream file(fileName.GetCStr());
	if (!file.is_open())
	{
		Console::WriteLine("Unable to open the file ", fileName);
		return data;
	}

	string line;
	while (getline(file, line))
	{
		auto row = ParseCsvRow(line.c_str());
		data->AddRow(std::move(row));
	}

	file.close();

	return data;
}
