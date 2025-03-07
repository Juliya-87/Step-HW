#pragma once

class StorageTransactionHandler
{
public:
	virtual void PrepareTransaction() = 0;
	virtual void CommitTransaction() = 0;
	virtual void RollbackTransaction() = 0;
	virtual bool HasActiveTransaction() const = 0;

	virtual ~StorageTransactionHandler() = default;

protected:
	StorageTransactionHandler() = default;
};
