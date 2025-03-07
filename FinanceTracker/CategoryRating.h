#pragma once
#include "Report.h"

class CategoryRating final : public Report
{
public:
	CategoryRating(const std::shared_ptr<ReportDataSource>& reportDataSource, const std::shared_ptr<FileHandler>& csvFileHandler, const std::shared_ptr<Settings>& settings);

protected:
	MyString GetFileName() const override;
	std::unique_ptr<ReportData> GetReportData(ReportingPeriod period) const override;

private:
	static constexpr char REPORT_NAME[] = "Category Rating";
	static constexpr int NUMBER_OF_ITEMS = 3;
};
