#pragma once

#include "FileStorageTransactionHandler.h"

class StorageTransaction final
{
public:
	StorageTransaction(const std::shared_ptr<StorageTransactionHandler>& storageTransactionHandler);
	~StorageTransaction();

	bool GetIsActive() const;

	void Commit();
	void Rollback();

private:
	std::shared_ptr<StorageTransactionHandler> mStorageTransactionHandler;
	bool mIsActive;
};
