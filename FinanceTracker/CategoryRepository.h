#pragma once
#include "Category.h"
#include "ModelWithIdRepository.h"
#include "SpendingTransaction.h"

class CategoryRepository final : public ModelWithIdRepository<Category>
{
public:
	CategoryRepository(const std::shared_ptr<StorageManager<Category>>& storageManager,
		const std::shared_ptr<ModelWithIdRepository<SpendingTransaction>>& spendingTransactionRepository);

protected:
	bool CanDeleteItem(const Category& item) override;

private:
	std::shared_ptr<ModelWithIdRepository<SpendingTransaction>> mSpendingTransactionRepository;

	static constexpr char TABLE_NAME[] = "Categories";
};
