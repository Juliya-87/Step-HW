#pragma once
#include <ctime>

#include "MyString.h"
#include "ReportData.h"
#include "ReportDataSource.h"
#include "ReportingPeriod.h"

class Report
{
public:
	virtual ~Report() = default;

	void Print(ReportingPeriod period) const;
	void Export(ReportingPeriod period) const;

protected:
	Report(const std::shared_ptr<ReportDataSource>& reportDataSource, const std::shared_ptr<FileHandler>& csvFileHandler);

	virtual MyString GetFileName() const = 0;
	virtual std::unique_ptr<ReportData> GetReportData(ReportingPeriod period) const = 0;

	static time_t GetStartTime(ReportingPeriod period);

	std::shared_ptr<ReportDataSource> mReportDataSource = nullptr;

private:
	MyString GetFullFileName() const;

	std::shared_ptr<FileHandler> mFileHandler = nullptr;

	static constexpr char BASE_DIRECTORY[] = "Reports";
	static constexpr char SEPARATOR[] = ",";
};
