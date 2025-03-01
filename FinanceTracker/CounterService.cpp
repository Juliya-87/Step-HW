#include "CounterService.h"

using namespace std;

CounterService::CounterService(const shared_ptr<CounterRepository>& counterRepository) : mCounterRepository(counterRepository)
{
}

int CounterService::GetNextAccountId() const
{
	return GetNextValue("Account.Id");
}

int CounterService::GetNextCategoryId() const
{
	return GetNextValue("Category.Id");
}

int CounterService::GetNextTransactionId() const
{
	return GetNextValue("Transaction.Id");
}

int CounterService::GetNextValue(const MyString& name) const
{
	if (Counter* counter = mCounterRepository->GetByName(name))
	{
		const int nextValue = counter->GetNextValue();
		mCounterRepository->Update(counter);
		mCounterRepository->Save();
		return nextValue;
	}

	auto newCounter = make_unique<Counter>(name);
	const int nextValue = newCounter->GetNextValue();
	mCounterRepository->Add(std::move(newCounter));
	mCounterRepository->Save();
	return nextValue;
}
