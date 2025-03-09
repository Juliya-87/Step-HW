#pragma once
#include <optional>

#include "Counter.h"
#include "Repository.h"

class CounterRepository final : public Repository<Counter>
{
public:
	CounterRepository(const std::shared_ptr<StorageManager<Counter>>& storageManager);

	std::optional<std::reference_wrapper<Counter>> GetByName(const MyString& name);

private:
	static constexpr char TABLE_NAME[] = "Counters";
};
