#pragma once

class StorageTransactionHandler
{
public:
	virtual ~StorageTransactionHandler() = default;

	virtual void PrepareTransaction() = 0;
	virtual void CommitTransaction() = 0;
	virtual void RollbackTransaction() = 0;
	virtual bool HasActiveTransaction() const = 0;

protected:
	StorageTransactionHandler() = default;
};
