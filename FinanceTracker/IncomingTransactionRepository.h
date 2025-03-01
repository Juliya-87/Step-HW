#pragma once
#include "IncomingTransaction.h"
#include "TransactionRepository.h"

class IncomingTransactionRepository final : public TransactionRepository<IncomingTransaction>
{
public:
	IncomingTransactionRepository(const std::shared_ptr<StorageManager<IncomingTransaction>>& storageManager);

protected:
	MyString GetTableName() override;

private:
	static constexpr char TABLE_NAME[] = "Incoming Transactions";
};
