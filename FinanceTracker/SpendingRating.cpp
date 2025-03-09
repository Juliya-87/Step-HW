#include "SpendingRating.h"

#include <algorithm>

#include "ConversionHelpers.h"

using namespace std;

SpendingRating::SpendingRating(const shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository, const shared_ptr<FileHandler>& csvFileHandler, const shared_ptr<Settings>& settings)
	: Report(REPORT_NAME, spendingTransactionRepository, csvFileHandler, settings)
{
}

unique_ptr<ReportData> SpendingRating::GetReportData(const ReportingPeriod period) const
{
	const time_t startTime = GetStartTime(period);
	auto transactions = mSpendingTransactionRepository->GetTransactionsAfter(startTime);
	ranges::sort(transactions,
		[](const SpendingTransaction& item1, const SpendingTransaction& item2) { return item1.GetAmount() > item2.GetAmount(); });

	auto result = make_unique<ReportData>();

	ReportRow& header = result->CreateRow();
	header.AddCell(mReportName);

	ReportRow& columnNames = result->CreateRow();
	columnNames.AddCell("Time", 19);
	columnNames.AddCell("Amount", 10, false);
	columnNames.AddCell("Notes");

	for (size_t i = 0; i < NUMBER_OF_ITEMS && i < transactions.size(); i++)
	{
		const SpendingTransaction& transaction = transactions[i];
		ReportRow& row = result->CreateRow();
		row.AddCell(ToString(transaction.GetTransactionTime()), 19);
		row.AddCell(ToString(transaction.GetAmount(), 2), 10, false);
		row.AddCell(transaction.GetNotes());
	}

	return result;
}
