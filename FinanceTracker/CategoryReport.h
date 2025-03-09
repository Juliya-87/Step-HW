#pragma once
#include "Report.h"

class CategoryReport final : public Report
{
public:
	CategoryReport(const std::shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository, const std::shared_ptr<FileHandler>& csvFileHandler, const std::shared_ptr<Settings>& settings);

protected:
	std::unique_ptr<ReportData> GetReportData(ReportingPeriod period) const override;

private:
	static constexpr char REPORT_NAME[] = "Category Report";
};
