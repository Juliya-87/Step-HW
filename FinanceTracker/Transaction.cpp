#include "Transaction.h"

#include "ConversionHelpers.h"

Transaction::Transaction(const int id, const double amount, Account* account, const MyString& notes) : ModelBase(id), mNotes(notes)
{
	mAmount = amount;
	mAccountId = account->GetId();
	mAccount = account;
	mTransactionTime = time(nullptr);
}

double Transaction::GetAmount() const
{
	return mAmount;
}

int Transaction::GetAccountId() const
{
	return mAccountId;
}

Account* Transaction::GetAccount() const
{
	return mAccount;
}

const MyString& Transaction::GetNotes() const
{
	return mNotes;
}

time_t Transaction::GetTransactionTime() const
{
	return mTransactionTime;
}

void Transaction::InitAccount(Account* account)
{
	if (mAccount == nullptr && account->GetId() == mAccountId)
	{
		mAccount = account;
	}
}

void Transaction::Parse(MyString& str)
{
	ModelBase::Parse(str);

	char* chars = str.GetCStr();
	char* context = nullptr;
	char* endPtr = nullptr;

	char* token = strtok_s(chars, DELIMITER, &context);
	mAmount = strtod(token, &endPtr);

	token = strtok_s(nullptr, DELIMITER, &context);
	mAccountId = strtol(token, &endPtr, 10);

	token = strtok_s(nullptr, DELIMITER, &context);
	mNotes = MyString(token);

	token = strtok_s(nullptr, DELIMITER, &context);
	ParseTime(mTransactionTime, token);

	str = MyString(context);
}

MyString Transaction::ToString() const
{
	MyString str = ModelBase::ToString();
	str.Append(DELIMITER);
	str.Append(mAmount);
	str.Append(DELIMITER);
	str.Append(mAccountId);
	str.Append(DELIMITER);
	str.Append(mNotes);
	str.Append(DELIMITER);
	str.Append(mTransactionTime);
	return str;
}
