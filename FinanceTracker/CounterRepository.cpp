#include "CounterRepository.h"

using namespace std;

MyString CounterRepository::GetTableName()
{
	return {TABLE_NAME};
}

CounterRepository::CounterRepository(const std::shared_ptr<StorageManager<Counter>>& storageManager): Repository(storageManager)
{
}

Counter* CounterRepository::GetByName(const MyString& name)
{
	const auto& counters = GetAll();

	for (const auto& counter : counters)
	{
		if (counter->GetName() == name)
		{
			return counter.get();
		}
	}

	return nullptr;
}
