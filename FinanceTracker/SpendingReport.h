#pragma once
#include "Report.h"

class SpendingReport final : public Report
{
public:
	SpendingReport(const std::shared_ptr<ReportDataSource>& reportDataSource, const std::shared_ptr<FileHandler>& csvFileHandler, const std::shared_ptr<Settings>& settings);

protected:
	MyString GetFileName() const override;
	std::unique_ptr<ReportData> GetReportData(ReportingPeriod period) const override;

private:
	static constexpr char REPORT_NAME[] = "Spending Report";
};

