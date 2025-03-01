#include "IncomingTransactionRepository.h"

using namespace std;

IncomingTransactionRepository::IncomingTransactionRepository(
	const std::shared_ptr<StorageManager<IncomingTransaction>>& storageManager): TransactionRepository(storageManager)
{
}

MyString IncomingTransactionRepository::GetTableName()
{
	return { TABLE_NAME };
}
