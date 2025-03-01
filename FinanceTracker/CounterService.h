#pragma once
#include "CounterRepository.h"
#include "MyString.h"

class CounterService final
{
public:
	CounterService(const std::shared_ptr<CounterRepository>& counterRepository);

	int GetNextAccountId() const;
	int GetNextCategoryId() const;
	int GetNextTransactionId() const;

private:
	int GetNextValue(const MyString& name) const;

	std::shared_ptr<CounterRepository> mCounterRepository;
};
