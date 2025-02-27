#include "SpendingRating.h"

#include <algorithm>

#include "ConversionHelpers.h"

using namespace std;

MyString SpendingRating::GetFileName() const
{
	return { REPORT_NAME };
}

unique_ptr<ReportData> SpendingRating::GetReportData(const ReportingPeriod period) const
{
	const time_t startTime = GetStartTime(period);
	vector<SpendingTransaction*> transactions = mReportDataSource->GetTransactions(startTime);
	ranges::sort(transactions,
		[](const SpendingTransaction* item1, const SpendingTransaction* item2) { return item1->GetAmount() > item2->GetAmount(); });

	auto result = std::make_unique<ReportData>();

	ReportRow* header = result->AddRow();
	header->AddCell(REPORT_NAME);

	ReportRow* columnNames = result->AddRow();
	columnNames->AddCell("Time", 19);
	columnNames->AddCell("Amount", 10, false);
	columnNames->AddCell("Notes");

	for (size_t i = 0; i < NUMBER_OF_ITEMS && i < transactions.size(); i++)
	{
		const SpendingTransaction* transaction = transactions[i];
		ReportRow* row = result->AddRow();
		row->AddCell(ToString(transaction->GetTransactionTime()), 19);
		row->AddCell(ToString(transaction->GetAmount(), 2), 10, false);
		row->AddCell(transaction->GetNotes());
	}

	return result;
}

SpendingRating::SpendingRating(const shared_ptr<ReportDataSource>& reportDataSource) : Report(reportDataSource)
{
}
