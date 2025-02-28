#include "ReportRow.h"

using namespace std;

const vector<unique_ptr<ReportCell>>& ReportRow::GetCells() const
{
	return mCells;
}

void ReportRow::AddCell(const MyString& value, const std::streamsize width, const bool isLeftAligned)
{
	mCells.emplace_back(make_unique<ReportCell>(value, width, isLeftAligned));
}
