#include "CategoryReport.h"

#include "ConversionHelpers.h"

using namespace std;

CategoryReport::CategoryReport(const shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository,
	const shared_ptr<FileHandler>& csvFileHandler, const shared_ptr<Settings>& settings)
	: Report(REPORT_NAME, spendingTransactionRepository, csvFileHandler, settings)
{
}

unique_ptr<ReportData> CategoryReport::GetReportData(const ReportingPeriod period) const
{
	const time_t startTime = GetStartTime(period);
	const auto statistics = mSpendingTransactionRepository->GetCategorySpendingStatistics(startTime);
	auto result = make_unique<ReportData>();

	ReportRow& header = result->CreateRow();
	header.AddCell(mReportName);

	ReportRow& columnNames = result->CreateRow();
	columnNames.AddCell("Category", 20);
	columnNames.AddCell("Amount", 10, false);

	double total = 0;

	for (auto& [categoryRef, amount] : statistics)
	{
		Category& category = categoryRef.get();
		ReportRow& row = result->CreateRow();
		row.AddCell(category.GetName(), 20);
		row.AddCell(ToString(amount, 2), 10, false);

		total += amount;
	}

	ReportRow& totalRow = result->CreateRow();
	totalRow.AddCell("Total:", 20);
	totalRow.AddCell(ToString(total, 2), 10, false);

	return result;
}
