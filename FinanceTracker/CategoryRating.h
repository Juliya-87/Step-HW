#pragma once
#include "Report.h"

class CategoryRating : public Report
{
private:
	static constexpr char REPORT_NAME[] = "Category Rating";
	static constexpr int NUMBER_OF_ITEMS = 3;

protected:
	MyString GetFileName() const override;

	std::unique_ptr<ReportData> GetReportData(ReportingPeriod period) const override;

public:
	CategoryRating(const std::shared_ptr<ReportDataSource>& reportDataSource, const std::shared_ptr<FileHandler>& csvFileHandler);
};
