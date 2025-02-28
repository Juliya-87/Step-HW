#include "ReportData.h"

using namespace std;

const vector<unique_ptr<ReportRow>>& ReportData::GetRows() const
{
	return mRows;
}

ReportRow* ReportData::CreateRow()
{
	const auto& row = mRows.emplace_back(make_unique<ReportRow>());
	return row.get();
}
