#include "CounterService.h"

using namespace std;

int CounterService::GetNextValue(const MyString& name) const
{
	const vector<Counter*> counters = mCounterRepository->GetAll();

	for (Counter* counter : counters)
	{
		if (counter->GetName() == name)
		{
			const int nextValue = counter->GetNextValue();
			mCounterRepository->Save();
			return nextValue;
		}
	}

	const auto newCounter = new Counter(name);
	const int nextValue = newCounter->GetNextValue();
	mCounterRepository->AddOrUpdate(newCounter);
	mCounterRepository->Save();
	return nextValue;
}

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
