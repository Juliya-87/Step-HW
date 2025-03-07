#include "FileRow.h"

using namespace std;

const vector<unique_ptr<FileCell>>& FileRow::GetCells() const
{
	return mCells;
}

bool FileRow::IsEmpty() const
{
	return mCells.empty();
}

void FileRow::AddCell(const MyString& value)
{
	mCells.emplace_back(make_unique<FileCell>(value));
}

void FileRow::AddCell(MyString&& value)
{
	mCells.emplace_back(make_unique<FileCell>(std::move(value)));
}
