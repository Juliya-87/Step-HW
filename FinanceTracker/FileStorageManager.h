#pragma once
#include <ranges>

#include "CsvFileHandler.h"
#include "MyString.h"
#include "Serializable.h"
#include "StorageManager.h"

template <is_serializable T>
class FileStorageManager final : public StorageManager<T>
{
public:
	FileStorageManager(const std::shared_ptr<FileHandler>& fileHandler) : mFileHandler(fileHandler)
	{
	}

	void Save(const MyString& tableName, const std::vector<std::unique_ptr<T>>& items) override
	{
		if (items.empty())
		{
			return;
		}

		const MyString fileName = GetFileName(tableName);
		const auto data = std::make_unique<FileData>();
		auto sample = items[0]->ToMap();

		FileRow* header = data->CreateRow();
		for (const auto& fieldName : sample | std::views::keys)
		{
			header->AddCell(fieldName);
		}

		for (const auto& obj : items)
		{
			auto map = obj->ToMap();
			FileRow* row = data->CreateRow();
			for (const auto& fieldValue : map | std::views::values)
			{
				row->AddCell(fieldValue);
			}
		}

		mFileHandler->SaveToFile(fileName, data);
	}

	std::vector<std::unique_ptr<T>> Load(const MyString& tableName) override
	{
		const MyString fileName = GetFileName(tableName);
		const auto& data = mFileHandler->LoadFromFile(fileName);
		if (data->IsEmpty())
		{
			return {};
		}

		const FileRow* headers = data->At(0);
		if (headers->IsEmpty())
		{
			return {};
		}

		std::vector<std::unique_ptr<T>> items;
		for (size_t rowIndex = 1; rowIndex < data->GetSize(); rowIndex++)
		{
			const FileRow* values = data->At(rowIndex);
			auto map = GetMap(headers, values);
			if (map.empty())
			{
				continue;
			}

			auto obj = std::make_unique<T>();
			obj->FromMap(map);
			items.push_back(std::move(obj));
		}

		return items;
	}

private:
	MyString GetFileName(const MyString& tableName) const
	{
		MyString fileName(BASE_DIRECTORY);
		fileName.Append("\\");
		fileName.Append(tableName);
		fileName.Append(mFileHandler->GetExtension());
		return fileName;
	}

	static std::unordered_map<MyString, MyString> GetMap(const FileRow* header, const FileRow* values)
	{
		auto& headerCells = header->GetCells();
		auto& valuesCells = values->GetCells();

		if (headerCells.size() != valuesCells.size())
		{
			return {};
		}

		std::unordered_map<MyString, MyString> map;
		for (size_t i = 0; i < headerCells.size(); i++)
		{
			map.emplace(headerCells[i]->GetValue(), valuesCells[i]->GetValue());
		}

		return map;
	}

	std::shared_ptr<FileHandler> mFileHandler;

	static constexpr char BASE_DIRECTORY[] = "Data";
};
