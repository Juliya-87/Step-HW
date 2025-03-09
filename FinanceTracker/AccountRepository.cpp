#include "AccountRepository.h"

#include "IncomingTransactionRepository.h"
#include "SpendingTransactionRepository.h"

using namespace std;

AccountRepository::AccountRepository(const shared_ptr<StorageManager<Account>>& storageManager,
	const shared_ptr<ModelWithIdRepository<IncomingTransaction>>& incomingTransactionRepository,
	const shared_ptr<ModelWithIdRepository<SpendingTransaction>>& spendingTransactionRepository)
	: ModelWithIdRepository(TABLE_NAME, storageManager),
	mIncomingTransactionRepository(incomingTransactionRepository),
	mSpendingTransactionRepository(spendingTransactionRepository)
{
}

bool AccountRepository::CanDeleteItem(const Account& item)
{
	const auto incomingTransactions = mIncomingTransactionRepository->GetByPredicate(
		[item](const IncomingTransaction& transaction) { return transaction.GetAccount() == item; });

	const auto spendingTransactions = mSpendingTransactionRepository->GetByPredicate(
		[item](const SpendingTransaction& transaction) { return transaction.GetAccount() == item; });

	return incomingTransactions.empty() && spendingTransactions.empty();
}
