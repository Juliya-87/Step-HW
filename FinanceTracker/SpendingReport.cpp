#include "SpendingReport.h"

#include "ConversionHelpers.h"

using namespace std;

MyString SpendingReport::GetFileName() const
{
	return {REPORT_NAME};
}

unique_ptr<ReportData> SpendingReport::GetReportData(const ReportingPeriod period) const
{
	const time_t startTime = GetStartTime(period);
	const auto transactions = mReportDataSource->GetTransactions(startTime);
	auto result = make_unique<ReportData>();

	ReportRow* header = result->CreateRow();
	header->AddCell(REPORT_NAME);

	ReportRow* columnNames = result->CreateRow();
	columnNames->AddCell("Time", 19);
	columnNames->AddCell("Amount", 10, false);
	columnNames->AddCell("Notes");

	double total = 0;

	for (const auto transaction : transactions)
	{
		ReportRow* row = result->CreateRow();
		row->AddCell(ToString(transaction->GetTransactionTime()), 19);
		row->AddCell(ToString(transaction->GetAmount(), 2), 10, false);
		row->AddCell(transaction->GetNotes());

		total += transaction->GetAmount();
	}

	ReportRow* totalRow = result->CreateRow();
	totalRow->AddCell("Total:", 19);
	totalRow->AddCell(ToString(total, 2), 10, false);

	return result;
}

SpendingReport::SpendingReport(const shared_ptr<ReportDataSource>& reportDataSource, const shared_ptr<FileHandler>& csvFileHandler) : Report(reportDataSource, csvFileHandler)
{
}
