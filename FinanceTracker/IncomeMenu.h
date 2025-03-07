#pragma once
#include "AccountRepository.h"
#include "CounterService.h"
#include "IncomingTransactionRepository.h"
#include "StorageTransactionManager.h"

class IncomeMenu
{
public:
	IncomeMenu(const std::shared_ptr<AccountRepository>& accountRepository,
		const std::shared_ptr<IncomingTransactionRepository>& incomingTransactionRepository,
		const std::shared_ptr<CounterService>& counterService,
		const std::shared_ptr<StorageTransactionManager>& storageTransactionManager);

	void ShowMenu() const;

private:
	void List() const;
	void Add() const;
	void Delete() const;

	std::shared_ptr<AccountRepository> mAccountRepository;
	std::shared_ptr<IncomingTransactionRepository> mIncomingTransactionRepository;
	std::shared_ptr<CounterService> mCounterService;
	std::shared_ptr<StorageTransactionManager> mStorageTransactionManager;
};
