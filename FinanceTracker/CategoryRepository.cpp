#include "CategoryRepository.h"

#include <algorithm>

using namespace std;

MyString CategoryRepository::GetFileName()
{
	return { FILE_NAME };
}

bool CategoryRepository::IsItemUsedInOtherRepository(Category* item)
{
	const vector<SpendingTransaction*> spendingTransactions = mSpendingTransactionRepository->GetAll();
	const bool hasSpendingTransactions = ranges::any_of(spendingTransactions,
	                                                    [item](const SpendingTransaction* transaction) { return *transaction->GetCategory() == *item; });

	return hasSpendingTransactions;
}

CategoryRepository::CategoryRepository(const shared_ptr<ModelRepository<SpendingTransaction>>& spendingTransactionRepository)
	: mSpendingTransactionRepository(spendingTransactionRepository)
{
}
