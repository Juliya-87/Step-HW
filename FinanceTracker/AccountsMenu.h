#pragma once

#include "AccountRepository.h"
#include "CounterService.h"

class AccountsMenu
{
private:
	std::shared_ptr<AccountRepository> mAccountRepository = nullptr;
	std::shared_ptr<CounterService> mCounterService = nullptr;

	void List() const;
	void Add() const;
	void Rename() const;
	void ChangeType() const;
	void Delete() const;

public:
	AccountsMenu(const std::shared_ptr<AccountRepository>& accountRepository, const std::shared_ptr<CounterService>& counterService);

	void ShowMenu() const;
};

