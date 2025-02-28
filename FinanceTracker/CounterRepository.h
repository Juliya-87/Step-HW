#pragma once
#include "Counter.h"
#include "Repository.h"

class CounterRepository final : public Repository<Counter>
{
private:
	static constexpr char TABLE_NAME[] = "Counters";

protected:
	MyString GetTableName() override;

public:
	CounterRepository(const std::shared_ptr<StorageManager<Counter>>& storageManager);

	Counter* GetByName(const MyString& name);
};
