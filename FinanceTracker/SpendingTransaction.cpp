#include "SpendingTransaction.h"

#include <cstdlib>

#include "StringTokenExtractor.h"

SpendingTransaction::SpendingTransaction(const int id, const double amount, Account* account, Category* category,
	const MyString& notes) : Transaction(id, amount, account, notes)
{
	mCategoryId = category->GetId();
	mCategory = category;
}

int SpendingTransaction::GetCategoryId() const
{
	return mCategoryId;
}

Category* SpendingTransaction::GetCategory() const
{
	return mCategory;
}

void SpendingTransaction::InitCategory(Category* category)
{
	if (mCategory == nullptr && category->GetId() == mCategoryId)
	{
		mCategory = category;
	}
}

void SpendingTransaction::Parse(MyString& str)
{
	Transaction::Parse(str);

	StringTokenExtractor splitter(str, DELIMITER);
	MyString token;
	char* endPtr = nullptr;

	splitter.GetNextToken(token);
	mCategoryId = strtol(token.GetCStr(), &endPtr, 10);

	str = splitter.GetRemaining();
}

MyString SpendingTransaction::ToString() const
{
	MyString str = Transaction::ToString();
	str.Append(DELIMITER);
	str.Append(mCategoryId);
	return str;
}
