#include "Report.h"

#include <fstream>

#include "Console.h"
#include "ConversionHelpers.h"
#include "TimeHelper.h"

using namespace std;

MyString Report::GetFullFileName() const
{
	const MyString fileName = GetFileName();

	MyString fullFileName(BASE_DIRECTORY);
	fullFileName.Append("\\");
	fullFileName.Append(fileName);
	fullFileName.Append(" ");
	fullFileName.Append(ToString(time(nullptr), "%Y-%m-%d %H%M%S"));
	fullFileName.Append(mFileHandler->GetExtension());

	return fullFileName;
}

Report::Report(const shared_ptr<ReportDataSource>& reportDataSource, const shared_ptr<FileHandler>& csvFileHandler) : mReportDataSource(reportDataSource), mFileHandler(csvFileHandler)
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
