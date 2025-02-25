#pragma once
#include "Account.h"
#include "IncomingTransaction.h"
#include "ModelRepository.h"
#include "SpendingTransactionRepository.h"

class AccountRepository final : public ModelRepository<Account>
{
private:
	static constexpr char FILE_NAME[] = "Accounts.txt";

	std::shared_ptr<ModelRepository<IncomingTransaction>> mIncomingTransactionRepository = nullptr;
	std::shared_ptr<ModelRepository<SpendingTransaction>> mSpendingTransactionRepository = nullptr;

protected:
	MyString GetFileName() override;

	bool IsItemUsedInOtherRepository(Account* item) override;

public:
	AccountRepository(const std::shared_ptr<ModelRepository<IncomingTransaction>>& incomingTransactionRepository,
		const std::shared_ptr<ModelRepository<SpendingTransaction>>& spendingTransactionRepository);
};
