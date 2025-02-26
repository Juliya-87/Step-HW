#include "Transaction.h"

#include "ConversionHelpers.h"
#include "StringTokenExtractor.h"

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

	StringTokenExtractor splitter(str, DELIMITER);
	MyString token;
	char* endPtr = nullptr;

	splitter.GetNextToken(token);
	mAmount = strtod(token.GetCStr(), &endPtr);

	splitter.GetNextToken(token);
	mAccountId = strtol(token.GetCStr(), &endPtr, 10);

	splitter.GetNextToken(token);
	mNotes = token;

	splitter.GetNextToken(token);
	ParseTime(mTransactionTime, token.GetCStr());

	str = splitter.GetRemaining();
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
