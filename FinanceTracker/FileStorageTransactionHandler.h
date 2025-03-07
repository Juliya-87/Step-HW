#pragma once
#include "MyString.h"
#include "Settings.h"
#include "StorageTransactionHandler.h"

class FileStorageTransactionHandler : public StorageTransactionHandler
{
public:
    FileStorageTransactionHandler(const std::shared_ptr<Settings>& settings);

    void PrepareTransaction() override;
    void CommitTransaction() override;
    void RollbackTransaction() override;
    bool HasActiveTransaction() const override;

private:
    MyString mDataBaseDirectory;
    MyString mTempDirectory;
    MyString mTransactionDirectory;

    static constexpr char TRANSACTION_DIRECTORY[] = "Transaction";
    static constexpr char TEMP_DIRECTORY[] = "TrnTmp";
};
