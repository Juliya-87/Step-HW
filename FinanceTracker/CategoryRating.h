#pragma once
#include "Report.h"

class CategoryRating final : public Report
{
public:
	CategoryRating(const std::shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository, const std::shared_ptr<FileHandler>& fileHandler, const std::shared_ptr<Settings>& settings);

protected:
	std::unique_ptr<ReportData> GetReportData(ReportingPeriod period) const override;

private:
	static constexpr char REPORT_NAME[] = "Category Rating";
	static constexpr int NUMBER_OF_ITEMS = 3;
};
