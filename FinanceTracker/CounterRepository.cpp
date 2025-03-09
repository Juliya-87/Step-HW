#include "CounterRepository.h"

using namespace std;

CounterRepository::CounterRepository(const shared_ptr<StorageManager<Counter>>& storageManager): Repository(TABLE_NAME, storageManager)
{
}

optional<reference_wrapper<Counter>> CounterRepository::GetByName(const MyString& name)
{
	return GetByKey(name);
}