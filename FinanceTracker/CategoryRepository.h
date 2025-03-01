#pragma once
#include "Category.h"
#include "ModelRepository.h"
#include "SpendingTransaction.h"

class CategoryRepository final : public ModelRepository<Category>
{
public:
	CategoryRepository(const std::shared_ptr<StorageManager<Category>>& storageManager,
		const std::shared_ptr<ModelRepository<SpendingTransaction>>& spendingTransactionRepository);

protected:
	MyString GetTableName() override;

	bool IsItemUsedInOtherRepository(const Category* item) override;

private:
	std::shared_ptr<ModelRepository<SpendingTransaction>> mSpendingTransactionRepository = nullptr;

	static constexpr char TABLE_NAME[] = "Categories";
};
