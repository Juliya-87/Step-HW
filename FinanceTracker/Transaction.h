#pragma once
#include <ctime>
#include <optional>

#include "Account.h"

class Transaction : public ModelWithId
{
public:
	double GetAmount() const;
	int GetAccountId() const;
	Account& GetAccount() const;
	const MyString& GetNotes() const;
	time_t GetTransactionTime() const;

	void InitializeAccount(Account& account);

	std::unordered_map<MyString, MyString> ToMap() const override;
	void FromMap(const std::unordered_map<MyString, MyString>& data) override;

protected:
	Transaction() = default;
	Transaction(int id, double amount, Account& account, const MyString& notes);

private:
	double mAmount = 0;
	int mAccountId = 0;
	std::optional<std::reference_wrapper<Account>> mAccount;
	MyString mNotes;
	time_t mTransactionTime = 0;
};
