#pragma once

#include "AccountRepository.h"
#include "CounterService.h"

class AccountsMenu
{
public:
	AccountsMenu(const std::shared_ptr<AccountRepository>& accountRepository, const std::shared_ptr<CounterService>& counterService);

	void ShowMenu() const;

private:
	void List() const;
	void Add() const;
	void Rename() const;
	void ChangeType() const;
	void Delete() const;

	std::shared_ptr<AccountRepository> mAccountRepository = nullptr;
	std::shared_ptr<CounterService> mCounterService = nullptr;
};

