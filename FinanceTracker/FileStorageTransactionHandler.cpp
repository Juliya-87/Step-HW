#include "FileStorageTransactionHandler.h"

#include <filesystem>

#include "FileHelper.h"

using namespace std;

FileStorageTransactionHandler::FileStorageTransactionHandler(const shared_ptr<Settings>& settings)
	: mDataBaseDirectory(settings->GetDataBaseDirectory()),
	mTempDirectory(mDataBaseDirectory + "\\" + TEMP_DIRECTORY),
	mTransactionDirectory(mDataBaseDirectory + "\\" + TRANSACTION_DIRECTORY)
{
}

void FileStorageTransactionHandler::PrepareTransaction()
{
	if (HasActiveTransaction())
	{
		throw runtime_error("Transaction already started");
	}

	try
	{
		CopyFilesOnly(mDataBaseDirectory, mTempDirectory);
		filesystem::rename(mTempDirectory.GetCStr(), mTransactionDirectory.GetCStr());
	}
	catch (...)
	{
		filesystem::remove_all(mTempDirectory.GetCStr());
		filesystem::remove_all(mTransactionDirectory.GetCStr());
		throw;
	}
}

void FileStorageTransactionHandler::CommitTransaction()
{
	filesystem::remove_all(mTransactionDirectory.GetCStr());
}

void FileStorageTransactionHandler::RollbackTransaction()
{
	if (HasActiveTransaction())
	{
		CopyFilesOnly(mTransactionDirectory, mDataBaseDirectory);
		filesystem::remove_all(mTransactionDirectory.GetCStr());
	}
}

bool FileStorageTransactionHandler::HasActiveTransaction() const
{
	return filesystem::exists(mTransactionDirectory.GetCStr());
}
