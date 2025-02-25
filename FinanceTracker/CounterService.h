#pragma once
#include "CounterRepository.h"
#include "MyString.h"

class CounterService final
{
private:
	std::shared_ptr<CounterRepository> mCounterRepository;

	int GetNextValue(const MyString& name) const;

public:
	CounterService(const std::shared_ptr<CounterRepository>& counterRepository);

	int GetNextAccountId() const;
	int GetNextCategoryId() const;
	int GetNextTransactionId() const;
};
