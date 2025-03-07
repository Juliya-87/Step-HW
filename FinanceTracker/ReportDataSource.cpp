#include "ReportDataSource.h"

using namespace std;

ReportDataSource::ReportDataSource(const shared_ptr<CategoryRepository>& categoryRepository,
	const shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository)
	: mCategoryRepository(categoryRepository), mSpendingTransactionRepository(spendingTransactionRepository)
{
}

vector<SpendingTransaction*> ReportDataSource::GetTransactions(const time_t startTime) const
{
	const auto& transactions = mSpendingTransactionRepository->GetAll();

	vector<SpendingTransaction*> result;
	for (const auto& transaction : transactions)
	{
		if (transaction->GetTransactionTime() >= startTime)
		{
			result.push_back(transaction.get());
		}
	}

	return result;
}

vector<pair<Category*, double>> ReportDataSource::GetCategoryStatistics(const time_t startTime) const
{
	const auto& categories = mCategoryRepository->GetAll();
	const auto transactions = GetTransactions(startTime);

	vector<pair<Category*, double>> result;
	for (const auto& category : categories)
	{
		double categoryAmount = 0;
		for (const auto transaction : transactions)
		{
			if (*transaction->GetCategory() == *category)
			{
				categoryAmount += transaction->GetAmount();
			}
		}

		result.emplace_back(category.get(), categoryAmount);
	}

	return result;
}
