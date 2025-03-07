#pragma once

#include "FileStorageTransactionHandler.h"

class StorageTransaction final
{
public:
	StorageTransaction(const std::shared_ptr<StorageTransactionHandler>& storageTransactionHandler);

	bool GetIsActive() const;

	void Commit();
	void Rollback();

	~StorageTransaction();

private:
	std::shared_ptr<StorageTransactionHandler> mStorageTransactionHandler;
	bool mIsActive;
};
