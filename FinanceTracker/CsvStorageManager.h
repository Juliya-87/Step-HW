#pragma once
#include <fstream>
#include <ranges>

#include "MyString.h"
#include "Serializable.h"

template <typename T>
concept is_serializable = std::is_base_of_v<Serializable, T>;

template <is_serializable T>
class CsvStorageManager final
{
private:
	static constexpr char DELIMITER = ',';

	static MyString EscapeCsvValue(const MyString& value)
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

			escapedValue.Insert(0, "\0");
			escapedValue.Insert(escapedValue.GetLength(), "\0");
		}

		return value;
	}

	static std::vector<MyString> ParseCsvRow(const MyString& line)
	{
		std::vector<MyString> result;
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
				result.push_back(value);
				value.Clear();
			}
			else
			{
				value.Append(1, ch);
			}
		}

		result.push_back(std::move(value)); // Add last value
		return result;
	}

public:
	static void SaveToCsv(const MyString& filename, const std::vector<T*>& items)
	{
		std::ofstream file(filename.GetCStr());
		if (!file.is_open())
		{
			Console::WriteLine("Unable to open the file ", filename);
			return;
		}

		if (items.empty())
		{
			file.close();
			return;
		}

		std::map<MyString, MyString> sample = items[0]->ToMap();
		bool isFirst = true;
		for (const MyString& fieldName : sample | std::views::keys)
		{
			if (!isFirst)
			{
				file << DELIMITER;
			}

			file << EscapeCsvValue(fieldName);
			isFirst = false;
		}
		file << "\n";

		for (T* obj : items)
		{
			std::map<MyString, MyString> row = obj->ToMap();
			isFirst = true;
			for (const auto& fieldValue : row | std::views::values)
			{
				if (!isFirst)
				{
					file << DELIMITER;
				}

				file << EscapeCsvValue(fieldValue);
			}
			file << "\n";
		}

		file.close();
	}

	static void LoadFromCsv(const MyString& filename, std::vector<T*>& items)
	{
		std::ifstream file(filename.GetCStr());
		if (!file.is_open())
		{
			Console::WriteLine("Unable to open the file ", filename);
			return;
		}

		std::string line;
		std::vector<MyString> headers;

		if (std::getline(file, line))
		{
			headers = ParseCsvRow(line.c_str());
		}

		while (std::getline(file, line))
		{
			std::vector<MyString> values = ParseCsvRow(line.c_str());
			if (values.size() != headers.size())
			{
				continue;
			}

			std::map<MyString, MyString> map;
			for (size_t i = 0; i < headers.size(); ++i)
			{
				map[headers[i]] = values[i];
			}

			T* obj = new T();
			obj->FromMap(map);
			items.push_back(obj);
		}

		file.close();
	}
};
