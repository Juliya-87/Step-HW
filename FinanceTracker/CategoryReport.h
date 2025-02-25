#pragma once
#include "Report.h"

class CategoryReport final : public Report
{
private:
	static constexpr char REPORT_NAME[] = "Category Report";

protected:
	MyString GetFileName() const override;

	std::unique_ptr<ReportData> GetReportData(ReportingPeriod period) const override;

public:
	CategoryReport(const std::shared_ptr<ReportDataSource>& reportDataSource);
};

