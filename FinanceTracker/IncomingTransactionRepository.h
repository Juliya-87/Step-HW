#pragma once
#include "IncomingTransaction.h"
#include "TransactionRepository.h"

class IncomingTransactionRepository final : public TransactionRepository<IncomingTransaction>
{
private:
	static constexpr char FILE_NAME[] = "Incoming Transactions.txt";

protected:
	MyString GetFileName() override;
};
