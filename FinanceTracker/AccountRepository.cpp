#include "AccountRepository.h"

#include <algorithm>

#include "IncomingTransactionRepository.h"
#include "SpendingTransactionRepository.h"

using namespace std;

MyString AccountRepository::GetTableName()
{
	return { TABLE_NAME };
}

bool AccountRepository::IsItemUsedInOtherRepository(const Account* item)
{
	const auto& incomingTransactions = mIncomingTransactionRepository->GetAll();
	const bool hasIncomingTransactions = ranges::any_of(incomingTransactions,
		[item](const unique_ptr<IncomingTransaction>& transaction) { return *transaction->GetAccount() == *item; });

	const auto& spendingTransactions = mSpendingTransactionRepository->GetAll();
	const bool hasSpendingTransactions = ranges::any_of(spendingTransactions,
		[item](const unique_ptr<SpendingTransaction>& transaction) { return *transaction->GetAccount() == *item; });

	return hasIncomingTransactions || hasSpendingTransactions;
}

AccountRepository::AccountRepository(const std::shared_ptr<StorageManager<Account>>& storageManager,
	const shared_ptr<ModelRepository<IncomingTransaction>>& incomingTransactionRepository,
	const shared_ptr<ModelRepository<SpendingTransaction>>& spendingTransactionRepository)
	: ModelRepository(storageManager),
	mIncomingTransactionRepository(incomingTransactionRepository),
	mSpendingTransactionRepository(spendingTransactionRepository)
{
}
