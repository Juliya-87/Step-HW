#include "StorageTransactionManager.h"

#include "StorageTransaction.h"

using namespace std;

StorageTransactionManager::StorageTransactionManager(const shared_ptr<StorageTransactionHandler>& storageTransactionHandler)
	: mStorageTransactionHandler(storageTransactionHandler)
{
	// Rollback the transaction if anything remains after a failure
	if (mStorageTransactionHandler->HasActiveTransaction())
	{
		mStorageTransactionHandler->RollbackTransaction();
	}
}

unique_ptr<StorageTransaction> StorageTransactionManager::BeginTransaction()
{
	mStorageTransactionHandler->PrepareTransaction();
	return make_unique<StorageTransaction>(mStorageTransactionHandler);
}
