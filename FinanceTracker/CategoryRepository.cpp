#include "CategoryRepository.h"

using namespace std;

CategoryRepository::CategoryRepository(const shared_ptr<StorageManager<Category>>& storageManager,
	const shared_ptr<ModelWithIdRepository<SpendingTransaction>>& spendingTransactionRepository)
	: ModelWithIdRepository(TABLE_NAME, storageManager),
	mSpendingTransactionRepository(spendingTransactionRepository)
{
}

bool CategoryRepository::CanDeleteItem(const Category& item)
{
	const auto spendingTransactions = mSpendingTransactionRepository->GetByPredicate(
		[item](const SpendingTransaction& transaction) { return transaction.GetCategory() == item; });

	return spendingTransactions.empty();
}
