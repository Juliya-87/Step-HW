#include "StorageTransaction.h"

#include <filesystem>

using namespace std;

StorageTransaction::StorageTransaction(const shared_ptr<StorageTransactionHandler>& storageTransactionHandler)
	: mStorageTransactionHandler(storageTransactionHandler), mIsActive(true)
{
}

bool StorageTransaction::GetIsActive() const
{
	return mIsActive;
}

void StorageTransaction::Commit()
{
	if (mIsActive)
	{
		mStorageTransactionHandler->CommitTransaction();
		mIsActive = false;
	}
}

void StorageTransaction::Rollback()
{
	if (mIsActive)
	{
		mStorageTransactionHandler->RollbackTransaction();
		mIsActive = false;
	}
}

StorageTransaction::~StorageTransaction()
{
	Rollback();
}
