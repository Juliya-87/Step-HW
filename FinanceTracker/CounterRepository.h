#pragma once
#include <optional>

#include "Counter.h"
#include "Repository.h"

class CounterRepository final : public Repository<Counter>
{
public:
	CounterRepository(const std::shared_ptr<StorageManager<Counter>>& storageManager);

	std::optional<Counter*> GetByName(const MyString& name);

protected:
	MyString GetTableName() override;

private:
	static constexpr char TABLE_NAME[] = "Counters";
};
