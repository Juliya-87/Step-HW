#pragma once
#include "AccountType.h"
#include "ModelBase.h"
#include "MyString.h"

class Account final : public ModelBase
{
public:
	Account() = default;
	Account(int id, const MyString& name, AccountType type);

	const MyString& GetName() const;
	AccountType GetType() const;
	double GetBalance() const;

	void Rename(const MyString& name);
	void ChangeType(AccountType type);
	void IncreaseBalance(double balance);
	void DecreaseBalance(double balance);

	std::unordered_map<MyString, MyString> ToMap() const override;
	void FromMap(const std::unordered_map<MyString, MyString>& data) override;

private:
	MyString mName;
	double mBalance = 0;
	AccountType mType = NONE;
};