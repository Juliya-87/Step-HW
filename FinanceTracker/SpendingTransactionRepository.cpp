#include "SpendingTransactionRepository.h"

using namespace std;

SpendingTransactionRepository::SpendingTransactionRepository(
	const shared_ptr<StorageManager<SpendingTransaction>>& storageManager) : TransactionRepository(TABLE_NAME, storageManager)
{
}

void SpendingTransactionRepository::InitializeCategoryRepository(
	const weak_ptr<ModelWithIdRepository<Category>>& categoryRepository)
{
	if (mCategoryRepository.expired())
	{
		mCategoryRepository = categoryRepository;
	}
}

vector<pair<reference_wrapper<Category>, double>> SpendingTransactionRepository::GetCategorySpendingStatistics(
	const time_t startTime)
{
	const shared_ptr<ModelWithIdRepository<Category>> categoryRepository = mCategoryRepository.lock();
	if (!categoryRepository)
	{
		throw runtime_error("Category repository is not initialized");
	}

	const auto categories = categoryRepository->GetAll();
	const auto transactions = GetTransactionsAfter(startTime);

	vector<pair<reference_wrapper<Category>, double>> result;
	for (Category& category : categories | views::transform(&reference_wrapper<Category>::get))
	{
		double categoryAmount = 0;
		for (const SpendingTransaction& transaction : transactions | views::transform(&reference_wrapper<SpendingTransaction>::get))
		{
			if (transaction.GetCategory() == category)
			{
				categoryAmount += transaction.GetAmount();
			}
		}

		result.emplace_back(category, categoryAmount);
	}

	return result;
}

void SpendingTransactionRepository::InitializeLoadedItem(SpendingTransaction& item)
{
	TransactionRepository::InitializeLoadedItem(item);

	const shared_ptr<ModelWithIdRepository<Category>> categoryRepository = mCategoryRepository.lock();
	if (!categoryRepository)
	{
		throw runtime_error("Category repository is not initialized");
	}

	const int categoryId = item.GetCategoryId();
	const auto optionalCategory = categoryRepository->GetById(categoryId);
	if (optionalCategory.has_value())
	{
		item.InitializeCategory(optionalCategory.value());
	}
}
