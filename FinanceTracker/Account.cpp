#include "Account.h"

#include "ConversionHelpers.h"

using namespace std;

Account::Account(const int id, const MyString& name, const AccountType type) : ModelBase(id), mName(name)
{
	mBalance = 0;
	mType = type;
}

const MyString& Account::GetName() const
{
	return mName;
}

AccountType Account::GetType() const
{
	return mType;
}

void Account::Rename(const MyString& name)
{
	mName = name;
}

void Account::ChangeType(const AccountType type)
{
	mType = type;
}

void Account::IncreaseBalance(const double balance)
{
	mBalance += balance;
}

void Account::DecreaseBalance(const double balance)
{
	mBalance -= balance;
}

std::map<MyString, MyString> Account::ToMap() const
{
	map<MyString, MyString> map = ModelBase::ToMap();

	map.emplace("Name", mName);
	map.emplace("Balance", ToString(mBalance, 2));
	map.emplace("Type", ToString(mType));

	return map;
}

void Account::FromMap(const std::map<MyString, MyString>& data)
{
	ModelBase::FromMap(data);

	mName = data.at("Name");
	mBalance = StrToDouble(data.at("Balance"));
	mType = StrToAccountType(data.at("Type"));
}
