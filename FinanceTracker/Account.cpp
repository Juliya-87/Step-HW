#include "Account.h"

void Account::Parse(MyString& str)
{
	ModelBase::Parse(str);

	char* chars = str.GetCStr();
	char* context = nullptr;
	char* endPtr = nullptr;

	char* token = strtok_s(chars, DELIMITER, &context);
	mName = MyString(token);

	token = strtok_s(nullptr, DELIMITER, &context);
	mBalance = strtod(token, &endPtr);

	token = strtok_s(nullptr, DELIMITER, &context);
	mType = static_cast<AccountType>(strtol(token, &endPtr, 10));

	str = MyString(context);
}

MyString Account::ToString() const
{
	MyString str = ModelBase::ToString();
	str.Append(DELIMITER);
	str.Append(mName);
	str.Append(DELIMITER);
	str.Append(mBalance);
	str.Append(DELIMITER);
	str.Append(mType);
	return str;
}

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
