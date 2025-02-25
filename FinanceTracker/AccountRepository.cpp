#include "AccountRepository.h"

#include <algorithm>

#include "IncomingTransactionRepository.h"
#include "SpendingTransactionRepository.h"

using namespace std;

MyString AccountRepository::GetFileName()
{
	return { FILE_NAME };
}

bool AccountRepository::IsItemUsedInOtherRepository(Account* item)
{
	const vector<IncomingTransaction*> incomingTransactions = mIncomingTransactionRepository->GetAll();
	const bool hasIncomingTransactions = ranges::any_of(incomingTransactions,
		[item](const IncomingTransaction* transaction) { return *transaction->GetAccount() == *item; });

	const vector<SpendingTransaction*> spendingTransactions = mSpendingTransactionRepository->GetAll();
	const bool hasSpendingTransactions = ranges::any_of(spendingTransactions,
		[item](const SpendingTransaction* transaction) { return *transaction->GetAccount() == *item; });

	return hasIncomingTransactions || hasSpendingTransactions;
}

AccountRepository::AccountRepository(const shared_ptr<ModelRepository<IncomingTransaction>>& incomingTransactionRepository,
	const shared_ptr<ModelRepository<SpendingTransaction>>& spendingTransactionRepository)
	: mIncomingTransactionRepository(incomingTransactionRepository), mSpendingTransactionRepository(spendingTransactionRepository)
{
}
