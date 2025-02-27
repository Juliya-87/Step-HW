#include "SpendingTransactionRepository.h"

using namespace std;

MyString SpendingTransactionRepository::GetFileName()
{
	return { FILE_NAME };
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

void SpendingTransactionRepository::InitializeCategoryRepository(
	const std::weak_ptr<ModelRepository<Category>>& categoryRepository)
{
	if (mCategoryRepository.expired())
	{
		mCategoryRepository = categoryRepository;
	}
}
