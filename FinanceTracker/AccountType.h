#pragma once
#include <cstdint>

enum AccountType : uint8_t
{
	NONE = 0,
	CREDIT_CARD = 1,
	DEBIT_CARD = 2,
	WALLET = 3
};
