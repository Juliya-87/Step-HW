#include "CategoryRating.h"

#include <algorithm>

#include "ConversionHelpers.h"

using namespace std;

CategoryRating::CategoryRating(const shared_ptr<ReportDataSource>& reportDataSource, const std::shared_ptr<FileHandler>& csvFileHandler): Report(reportDataSource, csvFileHandler)
{
}

MyString CategoryRating::GetFileName() const
{
	return { REPORT_NAME };
}

unique_ptr<ReportData> CategoryRating::GetReportData(const ReportingPeriod period) const
{
	const time_t startTime = GetStartTime(period);
	auto statistics = mReportDataSource->GetCategoryStatistics(startTime);
	ranges::sort(statistics,
		[](const pair<Category*, double> item1, const pair<Category*, double> item2) { return item1.second > item2.second; });

	auto result = make_unique<ReportData>();

	ReportRow* header = result->CreateRow();
	header->AddCell(REPORT_NAME);

	ReportRow* columnNames = result->CreateRow();
	columnNames->AddCell("Category", 20);
	columnNames->AddCell("Amount", 10, false);

	double total = 0;

	for (size_t i = 0; i < NUMBER_OF_ITEMS && i < statistics.size(); i++)
	{
		auto& [category, amount] = statistics[i];
		ReportRow* row = result->CreateRow();
		row->AddCell(category->GetName(), 20);
		row->AddCell(ToString(amount, 2), 10, false);

		total += amount;
	}

	ReportRow* totalRow = result->CreateRow();
	totalRow->AddCell("Total:", 20);
	totalRow->AddCell(ToString(total, 2), 10, false);

	return result;
}
