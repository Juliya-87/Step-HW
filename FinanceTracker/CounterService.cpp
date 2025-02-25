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
	const auto name = MyString("Account.Id");
	return GetNextValue(name);
}

int CounterService::GetNextCategoryId() const
{
	const auto name = MyString("Category.Id");
	return GetNextValue(name);
}

int CounterService::GetNextTransactionId() const
{
	const auto name = MyString("Transaction.Id");
	return GetNextValue(name);
}
