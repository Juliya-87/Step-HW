#pragma once

#include "MyString.h"
#include "Report.h"
#include "ReportingPeriod.h"

class SpendingReport final : public Report
{
private:
	static constexpr char REPORT_NAME[] = "Spending Report";

protected:
	MyString GetFileName() const override;

	std::unique_ptr<ReportData> GetReportData(ReportingPeriod period) const override;

public:
	SpendingReport(const std::shared_ptr<ReportDataSource>& reportDataSource, const std::shared_ptr<FileHandler>& csvFileHandler);
};

