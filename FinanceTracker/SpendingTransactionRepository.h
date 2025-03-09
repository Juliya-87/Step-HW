#pragma once
#include "ModelWithIdRepository.h"
#include "SpendingTransaction.h"
#include "TransactionRepository.h"

class SpendingTransactionRepository final : public TransactionRepository<SpendingTransaction>
{
public:
	SpendingTransactionRepository(const std::shared_ptr<StorageManager<SpendingTransaction>>& storageManager);

	void InitializeCategoryRepository(const std::weak_ptr<ModelWithIdRepository<Category>>& categoryRepository);

	std::vector<std::pair<std::reference_wrapper<Category>, double>> GetCategorySpendingStatistics(time_t startTime);

protected:
	void InitializeLoadedItem(SpendingTransaction& item) override;

private:
	std::weak_ptr<ModelWithIdRepository<Category>> mCategoryRepository;

	static constexpr char TABLE_NAME[] = "Spending Transactions";
};
