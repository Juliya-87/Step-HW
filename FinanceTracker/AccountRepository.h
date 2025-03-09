#pragma once
#include "Account.h"
#include "IncomingTransaction.h"
#include "ModelWithIdRepository.h"
#include "SpendingTransactionRepository.h"

class AccountRepository final : public ModelWithIdRepository<Account>
{
public:
	AccountRepository(const std::shared_ptr<StorageManager<Account>>& storageManager,
		const std::shared_ptr<ModelWithIdRepository<IncomingTransaction>>& incomingTransactionRepository,
		const std::shared_ptr<ModelWithIdRepository<SpendingTransaction>>& spendingTransactionRepository);

protected:
	bool CanDeleteItem(const Account& item) override;

private:
	std::shared_ptr<ModelWithIdRepository<IncomingTransaction>> mIncomingTransactionRepository;
	std::shared_ptr<ModelWithIdRepository<SpendingTransaction>> mSpendingTransactionRepository;

	static constexpr char TABLE_NAME[] = "Accounts";
};
