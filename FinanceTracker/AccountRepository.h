#pragma once
#include "Account.h"
#include "IncomingTransaction.h"
#include "ModelRepository.h"
#include "SpendingTransactionRepository.h"

class AccountRepository final : public ModelRepository<Account>
{
private:
	static constexpr char TABLE_NAME[] = "Accounts";

	std::shared_ptr<ModelRepository<IncomingTransaction>> mIncomingTransactionRepository = nullptr;
	std::shared_ptr<ModelRepository<SpendingTransaction>> mSpendingTransactionRepository = nullptr;

protected:
	MyString GetTableName() override;

	bool IsItemUsedInOtherRepository(const Account* item) override;

public:
	AccountRepository(const std::shared_ptr<StorageManager<Account>>& storageManager,
		const std::shared_ptr<ModelRepository<IncomingTransaction>>& incomingTransactionRepository,
		const std::shared_ptr<ModelRepository<SpendingTransaction>>& spendingTransactionRepository);
};
