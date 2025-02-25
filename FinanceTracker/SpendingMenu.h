#pragma once
#include "AccountRepository.h"
#include "CategoryRepository.h"
#include "CounterService.h"
#include "SpendingTransactionRepository.h"

class SpendingMenu
{
private:
	std::shared_ptr<AccountRepository> mAccountRepository = nullptr;
	std::shared_ptr<CategoryRepository> mCategoryRepository = nullptr;
	std::shared_ptr<SpendingTransactionRepository> mSpendingTransactionRepository = nullptr;
	std::shared_ptr<CounterService> mCounterService = nullptr;

	void List() const;
	void Add() const;
	void Delete() const;

public:
	SpendingMenu(const std::shared_ptr<AccountRepository>& accountRepository, const std::shared_ptr<CategoryRepository>& categoryRepository,
		const std::shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository, const std::shared_ptr<CounterService>& counterService);

	void ShowMenu() const;
};

