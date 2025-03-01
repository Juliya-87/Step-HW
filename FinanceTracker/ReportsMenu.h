#pragma once
#include "CategoryRating.h"
#include "CategoryReport.h"
#include "SpendingRating.h"
#include "SpendingReport.h"

class ReportsMenu
{
public:
	ReportsMenu(const std::shared_ptr<SpendingReport>& spendingReport, const std::shared_ptr<CategoryReport>& categoryReport,
		const std::shared_ptr<SpendingRating>& spendingRating, const std::shared_ptr<CategoryRating>& categoryRating);

	void ShowMenu() const;

private:
	static void PrintReport(const Report* report);

	std::shared_ptr<SpendingReport> mSpendingReport = nullptr;
	std::shared_ptr<CategoryReport> mCategoryReport = nullptr;
	std::shared_ptr<SpendingRating> mSpendingRating = nullptr;
	std::shared_ptr<CategoryRating> mCategoryRating = nullptr;
};

