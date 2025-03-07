#include "CounterRepository.h"

using namespace std;

CounterRepository::CounterRepository(const shared_ptr<StorageManager<Counter>>& storageManager): Repository(storageManager)
{
}

optional<Counter*> CounterRepository::GetByName(const MyString& name)
{
	const auto& counters = GetAll();

	for (const auto& counter : counters)
	{
		if (counter->GetName() == name)
		{
			return counter.get();
		}
	}

	return nullopt;
}

MyString CounterRepository::GetTableName()
{
	return { TABLE_NAME };
}