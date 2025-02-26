#pragma once
#include "ModelRepository.h"
#include "Transaction.h"

template <typename T>
concept is_transaction = std::is_base_of_v<Transaction, T>;

template <is_transaction T>
class TransactionRepository : public ModelRepository<T>
{
private:
	std::weak_ptr<ModelRepository<Account>> mAccountRepository;

protected:
	TransactionRepository() = default;

	void AfterDeserialized(T* item) override
	{
		const std::shared_ptr<ModelRepository<Account>> accountRepository = mAccountRepository.lock();
		if (!accountRepository)
		{
			return;
		}

		const auto transaction = item;
		const int accountId = transaction->GetAccountId();
		Account* account = accountRepository->GetById(accountId);
		transaction->InitAccount(account);
	}

public:
	void InitAccountRepository(const std::weak_ptr<ModelRepository<Account>>& accountRepository)
	{
		if (mAccountRepository.expired())
		{
			mAccountRepository = accountRepository;
		}
	}
};
