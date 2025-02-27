#include "CategoryReport.h"

#include "ConversionHelpers.h"

using namespace std;

MyString CategoryReport::GetFileName() const
{
	return { REPORT_NAME };
}

unique_ptr<ReportData> CategoryReport::GetReportData(const ReportingPeriod period) const
{
	const time_t startTime = GetStartTime(period);
	const vector<pair<Category*, double>> statistics = mReportDataSource->GetCategoryStatistics(startTime);
	auto result = make_unique<ReportData>();

	ReportRow* header = result->AddRow();
	header->AddCell(REPORT_NAME);

	ReportRow* columnNames = result->AddRow();
	columnNames->AddCell("Category", 20);
	columnNames->AddCell("Amount", 10, false);

	double total = 0;

	for (auto& [category, amount] : statistics)
	{
		ReportRow* row = result->AddRow();
		row->AddCell(category->GetName(), 20);
		row->AddCell(ToString(amount, 2), 10, false);

		total += amount;
	}

	ReportRow* totalRow = result->AddRow();
	totalRow->AddCell("Total:", 20);
	totalRow->AddCell(ToString(total, 2), 10, false);

	return result;
}

CategoryReport::CategoryReport(const shared_ptr<ReportDataSource>& reportDataSource) : Report(reportDataSource)
{
}
