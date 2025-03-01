#pragma once
#include "AccountRepository.h"
#include "CounterService.h"
#include "IncomingTransactionRepository.h"

class IncomeMenu
{
public:
	IncomeMenu(const std::shared_ptr<AccountRepository>& accountRepository, const std::shared_ptr<IncomingTransactionRepository>& incomingTransactionRepository, const std::shared_ptr<CounterService>& counterService);

	void ShowMenu() const;

private:
	void List() const;
	void Add() const;
	void Delete() const;

	std::shared_ptr<AccountRepository> mAccountRepository = nullptr;
	std::shared_ptr<CounterService> mCounterService = nullptr;
	std::shared_ptr<IncomingTransactionRepository> mIncomingTransactionRepository = nullptr;
};
