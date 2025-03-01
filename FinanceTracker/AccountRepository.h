#pragma once
#include "Account.h"
#include "IncomingTransaction.h"
#include "ModelRepository.h"
#include "SpendingTransactionRepository.h"

class AccountRepository final : public ModelRepository<Account>
{
public:
	AccountRepository(const std::shared_ptr<StorageManager<Account>>& storageManager,
		const std::shared_ptr<ModelRepository<IncomingTransaction>>& incomingTransactionRepository,
		const std::shared_ptr<ModelRepository<SpendingTransaction>>& spendingTransactionRepository);

protected:
	MyString GetTableName() override;

	bool IsItemUsedInOtherRepository(const Account* item) override;

private:
	std::shared_ptr<ModelRepository<IncomingTransaction>> mIncomingTransactionRepository = nullptr;
	std::shared_ptr<ModelRepository<SpendingTransaction>> mSpendingTransactionRepository = nullptr;

	static constexpr char TABLE_NAME[] = "Accounts";
};
