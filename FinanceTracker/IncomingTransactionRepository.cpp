#include "IncomingTransactionRepository.h"

using namespace std;

IncomingTransactionRepository::IncomingTransactionRepository(
	const shared_ptr<StorageManager<IncomingTransaction>>& storageManager): TransactionRepository(storageManager)
{
}

MyString IncomingTransactionRepository::GetTableName()
{
	return { TABLE_NAME };
}
