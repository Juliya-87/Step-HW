#pragma once
#include "Category.h"
#include "Transaction.h"

class SpendingTransaction final : public Transaction
{
private:
	int mCategoryId = 0;
	Category* mCategory = nullptr;

public:
	SpendingTransaction() = default;
	SpendingTransaction(int id, double amount, Account* account, Category* category, const MyString& notes);

	int GetCategoryId() const;
	Category* GetCategory() const;

	void InitializeCategory(Category* category);

	std::unordered_map<MyString, MyString> ToMap() const override;
	void FromMap(const std::unordered_map<MyString, MyString>& data) override;
};
