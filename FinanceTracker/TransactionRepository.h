#pragma once
#include "ModelRepository.h"
#include "Transaction.h"

template <typename T>
concept is_transaction = std::is_base_of_v<Transaction, T>;

template <is_transaction T>
class TransactionRepository : public ModelRepository<T>
{
public:
	void InitializeAccountRepository(const std::weak_ptr<ModelRepository<Account>>& accountRepository)
	{
		if (mAccountRepository.expired())
		{
			mAccountRepository = accountRepository;
		}
	}

protected:
	TransactionRepository(const std::shared_ptr<StorageManager<T>>& storageManager) : ModelRepository<T>(storageManager)
	{
	}

	void AfterDeserialized(T* item) override
	{
		const std::shared_ptr<ModelRepository<Account>> accountRepository = mAccountRepository.lock();
		if (!accountRepository)
		{
			return;
		}

		const int accountId = item->GetAccountId();
		const auto optionalAccount = accountRepository->GetById(accountId);
		if (optionalAccount.has_value())
		{
			item->InitializeAccount(optionalAccount.value());
		}
	}

private:
	std::weak_ptr<ModelRepository<Account>> mAccountRepository;
};
