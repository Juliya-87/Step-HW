#pragma once
#include "Category.h"
#include "ModelRepository.h"
#include "SpendingTransaction.h"

class CategoryRepository final : public ModelRepository<Category>
{
private:
	static constexpr char FILE_NAME[] = "Categories.txt";

	std::shared_ptr<ModelRepository<SpendingTransaction>> mSpendingTransactionRepository = nullptr;

protected:
	MyString GetFileName() override;

	bool IsItemUsedInOtherRepository(Category* item) override;

public:
	CategoryRepository(const std::shared_ptr<ModelRepository<SpendingTransaction>>& spendingTransactionRepository);
};
