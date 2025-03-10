#include "SpendingTransaction.h"

#include "ConversionHelpers.h"

using namespace std;

SpendingTransaction::SpendingTransaction(const int id, const double amount, Account& account, Category& category,
	const MyString& notes) : Transaction(id, amount, account, notes)
{
	mCategoryId = category.GetId();
	mCategory = category;
}

int SpendingTransaction::GetCategoryId() const
{
	return mCategoryId;
}

Category& SpendingTransaction::GetCategory() const
{
	if (mCategory.has_value())
	{
		return mCategory.value();
	}

	throw runtime_error("Category is not initialized");
}

void SpendingTransaction::InitializeCategory(Category& category)
{
	if (!mCategory.has_value() && category.GetId() == mCategoryId)
	{
		mCategory = category;
	}
}

unordered_map<MyString, MyString> SpendingTransaction::ToMap() const
{
	auto map = Transaction::ToMap();

	map.emplace("CategoryId", ToString(mCategoryId));

	return map;
}

void SpendingTransaction::FromMap(const unordered_map<MyString, MyString>& data)
{
	Transaction::FromMap(data);

	mCategoryId = StrToInt(data.at("CategoryId"));
}
