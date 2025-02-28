#include "CategoryRepository.h"

#include <algorithm>

using namespace std;

MyString CategoryRepository::GetTableName()
{
	return { TABLE_NAME };
}

bool CategoryRepository::IsItemUsedInOtherRepository(const Category* item)
{
	const auto& spendingTransactions = mSpendingTransactionRepository->GetAll();
	const bool hasSpendingTransactions = ranges::any_of(spendingTransactions,
		[item](const unique_ptr<SpendingTransaction>& transaction) { return *transaction->GetCategory() == *item; });

	return hasSpendingTransactions;
}

CategoryRepository::CategoryRepository(const std::shared_ptr<StorageManager<Category>>& storageManager,
	const shared_ptr<ModelRepository<SpendingTransaction>>& spendingTransactionRepository)
	: ModelRepository(storageManager),
	mSpendingTransactionRepository(spendingTransactionRepository)
{
}
