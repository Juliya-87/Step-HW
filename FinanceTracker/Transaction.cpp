#include "Transaction.h"

#include "ConversionHelpers.h"

using namespace std;

double Transaction::GetAmount() const
{
	return mAmount;
}

int Transaction::GetAccountId() const
{
	return mAccountId;
}

Account& Transaction::GetAccount() const
{
	if (mAccount.has_value())
	{
		return mAccount.value();
	}

	throw runtime_error("Account is not initialized");
}

const MyString& Transaction::GetNotes() const
{
	return mNotes;
}

time_t Transaction::GetTransactionTime() const
{
	return mTransactionTime;
}

void Transaction::InitializeAccount(Account& account)
{
	if (!mAccount.has_value() && account.GetId() == mAccountId)
	{
		mAccount = account;
	}
}

unordered_map<MyString, MyString> Transaction::ToMap() const
{
	auto map = ModelWithId::ToMap();

	map.emplace("Amount", ToString(mAmount, 2));
	map.emplace("AccountId", ToString(mAccountId));
	map.emplace("Notes", mNotes);
	map.emplace("TransactionTime", ToString(mTransactionTime));

	return map;
}

void Transaction::FromMap(const unordered_map<MyString, MyString>& data)
{
	ModelWithId::FromMap(data);

	mAmount = StrToDouble(data.at("Amount"));
	mAccountId = StrToInt(data.at("AccountId"));
	mNotes = data.at("Notes");
	mTransactionTime = StrToTime(data.at("TransactionTime"));
}

Transaction::Transaction(const int id, const double amount, Account& account, const MyString& notes) : ModelWithId(id), mNotes(notes)
{
	mAmount = amount;
	mAccountId = account.GetId();
	mAccount = account;
	mTransactionTime = time(nullptr);
}
