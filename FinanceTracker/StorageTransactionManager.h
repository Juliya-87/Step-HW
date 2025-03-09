#pragma once
#include "FileStorageTransactionHandler.h"
#include "StorageTransaction.h"

class StorageTransactionManager final
{
public:
	StorageTransactionManager(const std::shared_ptr<StorageTransactionHandler>& storageTransactionHandler);

	std::unique_ptr<StorageTransaction> BeginTransaction();

private:
	std::shared_ptr<StorageTransactionHandler> mStorageTransactionHandler;
};
