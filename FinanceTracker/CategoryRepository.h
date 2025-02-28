#pragma once
#include "Category.h"
#include "ModelRepository.h"
#include "SpendingTransaction.h"

class CategoryRepository final : public ModelRepository<Category>
{
private:
	static constexpr char TABLE_NAME[] = "Categories";

	std::shared_ptr<ModelRepository<SpendingTransaction>> mSpendingTransactionRepository = nullptr;

protected:
	MyString GetTableName() override;

	bool IsItemUsedInOtherRepository(const Category* item) override;

public:
	CategoryRepository(const std::shared_ptr<StorageManager<Category>>& storageManager,
		const std::shared_ptr<ModelRepository<SpendingTransaction>>& spendingTransactionRepository);
};
