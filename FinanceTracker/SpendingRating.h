#pragma once
#include "Report.h"

class SpendingRating final : public Report
{
private:
	static constexpr char REPORT_NAME[] = "Spending Rating";
	static constexpr int NUMBER_OF_ITEMS = 3;

protected:
	MyString GetFileName() const override;

	std::unique_ptr<ReportData> GetReportData(ReportingPeriod period) const override;

public:
	SpendingRating(const std::shared_ptr<ReportDataSource>& reportDataSource);
};

