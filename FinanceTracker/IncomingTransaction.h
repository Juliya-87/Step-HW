#pragma once
#include "Transaction.h"

class IncomingTransaction final : public Transaction
{
public:
	IncomingTransaction() = default;
	IncomingTransaction(int id, double amount, Account* account, const MyString& notes);
};

