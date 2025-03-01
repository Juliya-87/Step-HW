#include "SpendingTransactionRepository.h"

using namespace std;

SpendingTransactionRepository::SpendingTransactionRepository(
	const std::shared_ptr<StorageManager<SpendingTransaction>>& storageManager): TransactionRepository(storageManager)
{
}

void SpendingTransactionRepository::InitializeCategoryRepository(
	const std::weak_ptr<ModelRepository<Category>>& categoryRepository)
{
	if (mCategoryRepository.expired())
	{
		mCategoryRepository = categoryRepository;
	}
}

MyString SpendingTransactionRepository::GetTableName()
{
	return { TABLE_NAME };
}

void SpendingTransactionRepository::AfterDeserialized(SpendingTransaction* item)
{
	TransactionRepository::AfterDeserialized(item);

	const shared_ptr<ModelRepository<Category>> categoryRepository = mCategoryRepository.lock();
	if (!categoryRepository)
	{
		return;
	}

	const int categoryId = item->GetCategoryId();
	Category* category = categoryRepository->GetById(categoryId);
	item->InitializeCategory(category);
}
