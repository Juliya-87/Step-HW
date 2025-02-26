#include "Account.h"

#include "StringTokenExtractor.h"

using namespace std;

void Account::Parse(MyString& str)
{
	ModelBase::Parse(str);
		
	StringTokenExtractor splitter(str, DELIMITER);
	MyString token;
	char* endPtr = nullptr;

	splitter.GetNextToken(token);
	mName = token;

	splitter.GetNextToken(token);
	mBalance = strtod(token.GetCStr(), &endPtr);

	splitter.GetNextToken(token);
	mType = IntToAccountType(strtol(token.GetCStr(), &endPtr, 10));

	str = splitter.GetRemaining();
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
