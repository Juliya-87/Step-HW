#pragma once
#include "AccountRepository.h"
#include "CategoryRepository.h"
#include "CounterService.h"
#include "SpendingTransactionRepository.h"

class SpendingMenu
{
public:
	SpendingMenu(const std::shared_ptr<AccountRepository>& accountRepository, const std::shared_ptr<CategoryRepository>& categoryRepository,
		const std::shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository, const std::shared_ptr<CounterService>& counterService);

	void ShowMenu() const;

private:
	void List() const;
	void Add() const;
	void Delete() const;

	std::shared_ptr<AccountRepository> mAccountRepository;
	std::shared_ptr<CategoryRepository> mCategoryRepository;
	std::shared_ptr<SpendingTransactionRepository> mSpendingTransactionRepository;
	std::shared_ptr<CounterService> mCounterService;
};
