#pragma once
#include "Counter.h"
#include "Repository.h"

class CounterRepository final : public Repository<Counter>
{
private:
	static constexpr char FILE_NAME[] = "Counters.txt";

protected:
	MyString GetFileName() override;
};
