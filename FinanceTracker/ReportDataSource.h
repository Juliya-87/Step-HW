#pragma once
#include "CategoryRepository.h"
#include "SpendingTransactionRepository.h"

class ReportDataSource
{
public:
	ReportDataSource(const std::shared_ptr<CategoryRepository>& categoryRepository, const std::shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository);

	std::vector<SpendingTransaction*> GetTransactions(time_t startTime) const;
	std::vector<std::pair<Category*, double>> GetCategoryStatistics(time_t startTime) const;

private:
	std::shared_ptr<CategoryRepository> mCategoryRepository;
	std::shared_ptr<SpendingTransactionRepository> mSpendingTransactionRepository;
};

