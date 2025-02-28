#include "FileData.h"

using namespace std;

const std::vector<std::unique_ptr<FileRow>>& FileData::GetRows() const
{
	return mRows;
}

size_t FileData::GetSize() const
{
	return mRows.size();
}

bool FileData::IsEmpty() const
{
	return mRows.empty();
}

const FileRow* FileData::At(const size_t pos) const
{
	return mRows.at(pos).get();
}

FileRow* FileData::CreateRow()
{
	const auto& row = mRows.emplace_back(std::make_unique<FileRow>());
	return row.get();
}

void FileData::AddRow(std::unique_ptr<FileRow> row)
{
	mRows.push_back(std::move(row));
}
