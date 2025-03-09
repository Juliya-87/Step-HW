#include "IncomingTransactionRepository.h"

using namespace std;

IncomingTransactionRepository::IncomingTransactionRepository(
	const shared_ptr<StorageManager<IncomingTransaction>>& storageManager): TransactionRepository(TABLE_NAME, storageManager)
{
}
