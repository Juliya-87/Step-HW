#pragma once
#include "AccountType.h"
#include "ModelBase.h"
#include "MyString.h"

class Account final : public ModelBase
{
private:
	MyString mName;
	double mBalance = 0;
	AccountType mType = NONE;

public:
	Account() = default;
	Account(int id, const MyString& name, AccountType type);

	const MyString& GetName() const;
	AccountType GetType() const;

	void Rename(const MyString& name);
	void ChangeType(AccountType type);
	void IncreaseBalance(double balance);
	void DecreaseBalance(double balance);

	std::map<MyString, MyString> ToMap() const override;
	void FromMap(const std::map<MyString, MyString>& data) override;
};