#include "CategoryRating.h"

#include <algorithm>

using namespace std;

CategoryRating::CategoryRating(const shared_ptr<ReportDataSource>& reportDataSource): Report(reportDataSource)
{
}

MyString CategoryRating::GetFileName() const
{
	return { REPORT_NAME };
}

unique_ptr<ReportData> CategoryRating::GetReportData(const ReportingPeriod period) const
{
	const time_t startTime = GetStartTime(period);
	vector<pair<Category*, double>> statistics = mReportDataSource->GetCategoryStatistics(startTime);
	ranges::sort(statistics,
		[](const pair<Category*, double> item1, const pair<Category*, double> item2) { return item1.second > item2.second; });

	auto result = make_unique<ReportData>();

	ReportRow* header = result->AddRow();
	header->AddCell(REPORT_NAME);

	ReportRow* columnNames = result->AddRow();
	columnNames->AddCell("Category", 20);
	columnNames->AddCell("Amount", 10, false);

	double total = 0;

	for (size_t i = 0; i < NUMBER_OF_ITEMS && i < statistics.size(); i++)
	{
		auto& [category, amount] = statistics[i];
		ReportRow* row = result->AddRow();
		row->AddCell(category->GetName(), 20);
		row->AddCell(amount, 10, false);

		total += amount;
	}

	ReportRow* totalRow = result->AddRow();
	totalRow->AddCell("Total:", 20);
	totalRow->AddCell(total, 10, false);

	return result;
}
