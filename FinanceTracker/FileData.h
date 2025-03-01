#pragma once
#include <memory>
#include <vector>

#include "FileRow.h"

class FileData
{
public:
	const std::vector<std::unique_ptr<FileRow>>& GetRows() const;
	size_t GetSize() const;

	bool IsEmpty() const;
	const FileRow* At(size_t pos) const;
	FileRow* CreateRow();
	void AddRow(std::unique_ptr<FileRow> row);

private:
	std::vector<std::unique_ptr<FileRow>> mRows;
};
