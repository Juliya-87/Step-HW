#include "SpendingReport.h"

#include "ConversionHelpers.h"

using namespace std;

SpendingReport::SpendingReport(const shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository, const shared_ptr<FileHandler>& csvFileHandler, const shared_ptr<Settings>& settings)
	: Report(REPORT_NAME, spendingTransactionRepository, csvFileHandler, settings)
{
}

unique_ptr<ReportData> SpendingReport::GetReportData(const ReportingPeriod period) const
{
	const time_t startTime = GetStartTime(period);
	const auto transactions = mSpendingTransactionRepository->GetTransactionsAfter(startTime);
	auto result = make_unique<ReportData>();

	ReportRow& header = result->CreateRow();
	header.AddCell(mReportName);

	ReportRow& columnNames = result->CreateRow();
	columnNames.AddCell("Time", 19);
	columnNames.AddCell("Amount", 10, false);
	columnNames.AddCell("Notes");

	double total = 0;

	for (const SpendingTransaction& transaction : transactions | views::transform(&reference_wrapper<SpendingTransaction>::get))
	{
		ReportRow& row = result->CreateRow();
		row.AddCell(ToString(transaction.GetTransactionTime()), 19);
		row.AddCell(ToString(transaction.GetAmount(), 2), 10, false);
		row.AddCell(transaction.GetNotes());

		total += transaction.GetAmount();
	}

	ReportRow& totalRow = result->CreateRow();
	totalRow.AddCell("Total:", 19);
	totalRow.AddCell(ToString(total, 2), 10, false);

	return result;
}
