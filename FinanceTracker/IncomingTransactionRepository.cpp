#include "IncomingTransactionRepository.h"

using namespace std;

MyString IncomingTransactionRepository::GetTableName()
{
	return {TABLE_NAME};
}

IncomingTransactionRepository::IncomingTransactionRepository(
	const std::shared_ptr<StorageManager<IncomingTransaction>>& storageManager): TransactionRepository(storageManager)
{
}
