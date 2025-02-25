#pragma once
#include <ctime>

#include "MyString.h"
#include "ReportData.h"
#include "ReportDataSource.h"
#include "ReportingPeriod.h"

class Report
{
private:
	static constexpr char BASE_DIRECTORY[] = "Reports";
	static constexpr char FILE_EXTENSION[] = ".csv";
	static constexpr char SEPARATOR[] = ",";

	MyString GetFullFileName() const;

protected:
	std::shared_ptr<ReportDataSource> mReportDataSource = nullptr;

	Report(const std::shared_ptr<ReportDataSource>& reportDataSource);

	virtual MyString GetFileName() const = 0;
	virtual std::unique_ptr<ReportData> GetReportData(ReportingPeriod period) const = 0;

	static time_t GetStartTime(ReportingPeriod period);

public:
	void Print(ReportingPeriod period) const;

	void Export(ReportingPeriod period) const;

	virtual ~Report() = default;
};
