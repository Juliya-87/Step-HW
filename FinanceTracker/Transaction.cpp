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

void Transaction::InitializeAccount(Account* account)
{
	if (mAccount == nullptr && account->GetId() == mAccountId)
	{
		mAccount = account;
	}
}

std::unordered_map<MyString, MyString> Transaction::ToMap() const
{
	auto map = ModelBase::ToMap();

	map.emplace("Amount", ToString(mAmount, 2));
	map.emplace("AccountId", ToString(mAccountId));
	map.emplace("Notes", mNotes);
	map.emplace("TransactionTime", ToString(mTransactionTime));

	return map;
}

void Transaction::FromMap(const std::unordered_map<MyString, MyString>& data)
{
	ModelBase::FromMap(data);

	mAmount = StrToDouble(data.at("Amount"));
	mAccountId = StrToInt(data.at("AccountId"));
	mNotes = data.at("Notes");
	mTransactionTime = StrToTime(data.at("TransactionTime"));
}
