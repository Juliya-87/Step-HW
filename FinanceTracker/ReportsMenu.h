#pragma once
#include "CategoryRating.h"
#include "CategoryReport.h"
#include "SpendingRating.h"
#include "SpendingReport.h"

class ReportsMenu
{
private:
	std::shared_ptr<SpendingReport> mSpendingReport = nullptr;
	std::shared_ptr<CategoryReport> mCategoryReport = nullptr;
	std::shared_ptr<SpendingRating> mSpendingRating = nullptr;
	std::shared_ptr<CategoryRating> mCategoryRating = nullptr;

	static void PrintReport(const std::shared_ptr<Report>& report);

public:
	ReportsMenu(const std::shared_ptr<SpendingReport>& spendingReport, const std::shared_ptr<CategoryReport>& categoryReport,
		const std::shared_ptr<SpendingRating>& spendingRating, const std::shared_ptr<CategoryRating>& categoryRating);

	void ShowMenu() const;
};

