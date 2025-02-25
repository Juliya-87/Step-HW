#include "ReportData.h"

using namespace std;

const vector<std::unique_ptr<ReportRow>>& ReportData::GetRows() const
{
	return mRows;
}

ReportRow* ReportData::AddRow()
{
	mRows.emplace_back(make_unique<ReportRow>());
	return mRows.back().get();
}
