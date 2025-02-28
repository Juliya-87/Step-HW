#pragma once
#include "IncomingTransaction.h"
#include "TransactionRepository.h"

class IncomingTransactionRepository final : public TransactionRepository<IncomingTransaction>
{
private:
	static constexpr char TABLE_NAME[] = "Incoming Transactions";

protected:
	MyString GetTableName() override;

public:
	IncomingTransactionRepository(const std::shared_ptr<StorageManager<IncomingTransaction>>& storageManager);
};
