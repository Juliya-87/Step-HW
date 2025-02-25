#pragma once
#include <ctime>

#include "Account.h"

class Transaction : public ModelBase
{
private:
	double mAmount = 0;
	int mAccountId = 0;
	Account* mAccount = nullptr;
	MyString mNotes;
	time_t mTransactionTime = 0;

protected:
	Transaction() = default;
	Transaction(int id, double amount, Account* account, const MyString& notes);

public:
	double GetAmount() const;
	int GetAccountId() const;
	Account* GetAccount() const;
	const MyString& GetNotes() const;
	time_t GetTransactionTime() const;

	void InitAccount(Account* account);

	void Parse(MyString& str) override;
	MyString ToString() const override;
};

