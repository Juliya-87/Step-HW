#pragma once
#include "ModelRepository.h"
#include "SpendingTransaction.h"
#include "TransactionRepository.h"

class SpendingTransactionRepository final : public TransactionRepository<SpendingTransaction>
{
private:
	static constexpr char FILE_NAME[] = "Spending Transactions.txt";

	std::weak_ptr<ModelRepository<Category>> mCategoryRepository;

protected:
	MyString GetFileName() override;

	void AfterDeserialized(SpendingTransaction* item) override;

public:
	void InitCategoryRepository(const std::weak_ptr<ModelRepository<Category>>& categoryRepository);
};
