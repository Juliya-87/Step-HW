#include "SpendingTransaction.h"

#include <cstdlib>
#include <cstring>

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

	char* chars = str.GetCStr();
	char* context = nullptr;
	char* endPtr = nullptr;

	const char* token = strtok_s(chars, DELIMITER, &context);
	mCategoryId = strtol(token, &endPtr, 10);

	str = MyString(context);
}

MyString SpendingTransaction::ToString() const
{
	MyString str = Transaction::ToString();
	str.Append(DELIMITER);
	str.Append(mCategoryId);
	return str;
}
