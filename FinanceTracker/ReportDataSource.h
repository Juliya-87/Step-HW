#pragma once
#include "CategoryRepository.h"
#include "SpendingTransactionRepository.h"

class ReportDataSource
{
private:
	std::shared_ptr<CategoryRepository> mCategoryRepository = nullptr;
	std::shared_ptr<SpendingTransactionRepository> mSpendingTransactionRepository = nullptr;

public:
	ReportDataSource(const std::shared_ptr<CategoryRepository>& categoryRepository, const std::shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository);

	std::vector<SpendingTransaction*> GetTransactions(time_t startTime) const;
	std::vector<std::pair<Category*, double>> GetCategoryStatistics(time_t startTime) const;
};

