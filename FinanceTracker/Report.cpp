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
	fullFileName.Append(FILE_EXTENSION);

	return fullFileName;
}

Report::Report(const shared_ptr<ReportDataSource>& reportDataSource) : mReportDataSource(reportDataSource)
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
	const unique_ptr<ReportData> reportData = GetReportData(period);

	for (const auto& row : reportData->GetRows())
	{
		for (const auto& cell : row->GetCells())
		{
			Console::WriteAligned(cell->GetValue(), cell->GetWidth(), cell->GetIsLeftAligned());
			Console::Write(' ');
		}

		Console::WriteLine();
	}
}

void Report::Export(const ReportingPeriod period) const
{
	const unique_ptr<ReportData> reportData = GetReportData(period);
	const MyString fullFileName = GetFullFileName();

	ofstream file(fullFileName.GetCStr());
	if (!file.is_open())
	{
		Console::WriteLine("Unable to open the file ", fullFileName);
		return;
	}

	for (const auto& row : reportData->GetRows())
	{
		bool isFirstColumn = true;
		for (const auto& cell : row->GetCells())
		{
			file << (isFirstColumn ? "" : SEPARATOR) << cell->GetValue();
			isFirstColumn = false;
		}

		file << '\n';
	}

	Console::WriteLine("Report successfully exported to: ", fullFileName);
}
