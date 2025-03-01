#pragma once
#include "ModelRepository.h"
#include "SpendingTransaction.h"
#include "TransactionRepository.h"

class SpendingTransactionRepository final : public TransactionRepository<SpendingTransaction>
{
public:
	SpendingTransactionRepository(const std::shared_ptr<StorageManager<SpendingTransaction>>& storageManager);

	void InitializeCategoryRepository(const std::weak_ptr<ModelRepository<Category>>& categoryRepository);

protected:
	MyString GetTableName() override;

	void AfterDeserialized(SpendingTransaction* item) override;

private:
	std::weak_ptr<ModelRepository<Category>> mCategoryRepository;

	static constexpr char TABLE_NAME[] = "Spending Transactions";
};
