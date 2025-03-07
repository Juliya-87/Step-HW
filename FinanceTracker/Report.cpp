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
		FileRow* fileRow = fileData->CreateRow();
		for (const auto& reportCell : reportRow->GetCells())
		{
			fileRow->AddCell(reportCell->GetValue());
		}
	}

	mFileHandler->SaveToFile(fullFileName, fileData);

	Console::WriteLine("Report successfully exported to: ", fullFileName);
}

Report::Report(const shared_ptr<ReportDataSource>& reportDataSource, const shared_ptr<FileHandler>& csvFileHandler, const shared_ptr<Settings>& settings)
	: mReportDataSource(reportDataSource), mFileHandler(csvFileHandler), mSettings(settings)
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
	fullFileName.Append("\\");
	fullFileName.Append(GetFileName());
	fullFileName.Append(" ");
	fullFileName.Append(ToString(now, "%Y-%m-%d %H%M%S"));
	fullFileName.Append(mFileHandler->GetExtension());

	return fullFileName;
}
