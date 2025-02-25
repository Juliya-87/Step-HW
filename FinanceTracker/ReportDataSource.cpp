#include "ReportDataSource.h"

#include <algorithm>

using namespace std;

ReportDataSource::ReportDataSource(const std::shared_ptr<CategoryRepository>& categoryRepository,
	const std::shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository)
	: mCategoryRepository(categoryRepository), mSpendingTransactionRepository(spendingTransactionRepository)
{
}

std::vector<SpendingTransaction*> ReportDataSource::GetTransactions(const time_t startTime) const
{
	const vector<SpendingTransaction*> transactions = mSpendingTransactionRepository->GetAll();

	vector<SpendingTransaction*> result;
	ranges::copy_if(transactions, back_inserter(result),
		[startTime](const SpendingTransaction* transaction) { return transaction->GetTransactionTime() >= startTime; });

	return result;
}

vector<pair<Category*, double>> ReportDataSource::GetCategoryStatistics(const time_t startTime) const
{
	const vector<Category*> categories = mCategoryRepository->GetAll();
	const vector<SpendingTransaction*> transactions = GetTransactions(startTime);

	vector<pair<Category*, double>> result;
	for (Category* category : categories)
	{
		double categoryAmount = 0;
		for (const SpendingTransaction* transaction : transactions)
		{
			if (*transaction->GetCategory() == *category)
			{
				categoryAmount += transaction->GetAmount();
			}
		}

		result.emplace_back(category, categoryAmount);
	}

	return result;
}
