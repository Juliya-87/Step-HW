#include "IncomingTransaction.h"

IncomingTransaction::IncomingTransaction(const int id, const double amount, Account& account,
	                                     const MyString& notes) : Transaction(id, amount, account, notes)
{
}
