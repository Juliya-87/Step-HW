#pragma once
#include "ModelWithIdRepository.h"
#include "Transaction.h"

template <typename T>
concept is_transaction = std::is_base_of_v<Transaction, T>;

template <is_transaction T>
class TransactionRepository : public ModelWithIdRepository<T>
{
public:
	void InitializeAccountRepository(const std::weak_ptr<ModelWithIdRepository<Account>>& accountRepository)
	{
		if (mAccountRepository.expired())
		{
			mAccountRepository = accountRepository;
		}
	}

	std::vector<std::reference_wrapper<T>> GetTransactionsAfter(const time_t startTime)
	{
		return this->GetByPredicate(
			[&startTime](const T& transaction) { return transaction.GetTransactionTime() >= startTime; });
	}

protected:
	TransactionRepository(const MyString& tableName, const std::shared_ptr<StorageManager<T>>& storageManager) : ModelWithIdRepository<T>(tableName, storageManager)
	{
	}

	void InitializeLoadedItem(T& item) override
	{
		const std::shared_ptr<ModelWithIdRepository<Account>> accountRepository = mAccountRepository.lock();
		if (!accountRepository)
		{
			return;
		}

		const int accountId = item.GetAccountId();
		const auto optionalAccount = accountRepository->GetById(accountId);
		if (optionalAccount.has_value())
		{
			item.InitializeAccount(optionalAccount.value());
		}
	}

private:
	std::weak_ptr<ModelWithIdRepository<Account>> mAccountRepository;
};
