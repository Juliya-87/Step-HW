#pragma once
#include <vector>

#include "FileCell.h"

class FileRow
{
public:
	const std::vector<std::unique_ptr<FileCell>>& GetCells() const;

	bool IsEmpty() const;
	void AddCell(const MyString& value);
	void AddCell(MyString&& value);

private:
	std::vector<std::unique_ptr<FileCell>> mCells;
};
