#include "Report.h"

#include <fstream>

#include "Console.h"
#include "ConversionHelpers.h"
#include "TimeHelper.h"

using namespace std;

void Report::Print(const ReportingPeriod period) const
{
	const auto reportData = GetReportData(period);

	for (const auto& reportRow : reportData->GetRows())
	{
		for (const auto& reportCell : reportRow->GetCells())
		{
			Console::WriteAligned(reportCell->GetValue(), reportCell->GetWidth(), reportCell->GetIsLeftAligned());
			Console::Write(' ');
		}

		Console::WriteLine();
	}
}

void Report::Export(const ReportingPeriod period) const
{
	const auto reportData = GetReportData(period);
	const MyString fullFileName = GetFullFileName();
	const auto fileData = make_unique<FileData>();

	for (const auto& reportRow : reportData->GetRows())
	{
		FileRow& fileRow = fileData->CreateRow();
		for (const auto& reportCell : reportRow->GetCells())
		{
			fileRow.AddCell(reportCell->GetValue());
		}
	}

	mFileHandler->SaveToFile(fullFileName, fileData);

	Console::WriteLine("Report successfully exported to: ", fullFileName);
}

Report::Report(const MyString& reportName, const shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository,
	const shared_ptr<FileHandler>& fileHandler, const shared_ptr<Settings>& settings)
	: mReportName(reportName), mSpendingTransactionRepository(spendingTransactionRepository),
	mFileHandler(fileHandler), mSettings(settings)
{
}

time_t Report::GetStartTime(const ReportingPeriod period)
{
	const time_t now = time(nullptr);

	switch (period)
	{
	case DAY: return AddDays(now, -1);
	case WEEK: return AddDays(now, -7);
	case MONTH: return AddMonths(now, -1);
	default: return now;
	}
}

MyString Report::GetFullFileName() const
{
	const time_t now = time(nullptr);

	MyString fullFileName(mSettings->GetReportsBaseDirectory());
	fullFileName.Append(1, filesystem::path::preferred_separator);
	fullFileName.Append(mReportName);
	fullFileName.Append(" ");
	fullFileName.Append(ToString(now, TIME_FORMAT));
	fullFileName.Append(mFileHandler->GetExtension());

	return fullFileName;
}
