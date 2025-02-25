#include "SpendingMenu.h"

#include "AccountRepository.h"
#include "CategoryRepository.h"
#include "ConversionHelpers.h"

using namespace std;

void SpendingMenu::List() const
{
	const vector<SpendingTransaction*> transactions = mSpendingTransactionRepository->GetAll();

	if (transactions.empty()) {
		Console::WriteLine("No incoming transactions available.");
		return;
	}

	for (const SpendingTransaction* transaction : transactions)
	{
		char timeBuff[25];
		TimeToString(timeBuff, sizeof(timeBuff), transaction->GetTransactionTime());

		Console::WriteLine("ID: ", transaction->GetId(),
			", Account: ", transaction->GetAccount()->GetName().GetCStr(),
			", Amount: ", transaction->GetAmount(),
			", Category: ", transaction->GetCategory()->GetName().GetCStr(),
			", Notes: ", transaction->GetNotes().GetCStr(),
			", Time: ", timeBuff);
	}
}

void SpendingMenu::Add() const
{
	double amount;
	int accountId;
	int categoryId;
	MyString notes;
	Console::WriteLine("Choose account for the transaction:");
	for (const Account* account : mAccountRepository->GetAll())
	{
		Console::WriteLine(account->GetId(), ". ", account->GetName().GetCStr());
	}
	Console::Write("Your choice: ");
	Console::ReadLine(accountId);
	Console::WriteLine("Choose category for the transaction:");
	for (const Category* category : mCategoryRepository->GetAll())
	{
		Console::WriteLine(category->GetId(), ". ", category->GetName().GetCStr());
	}
	Console::Write("Your choice: ");
	Console::ReadLine(categoryId);
	Console::Write("Enter income amount: ");
	Console::ReadLine(amount);
	Console::Write("Enter notes: ");
	Console::ReadLine(notes);

	const int id = mCounterService->GetNextTransactionId();
	Account* account = mAccountRepository->GetById(accountId);
	Category* category = mCategoryRepository->GetById(categoryId);

	const auto newTransaction = new SpendingTransaction(id, amount, account, category, notes);
	mSpendingTransactionRepository->AddOrUpdate(newTransaction);
	mSpendingTransactionRepository->Save();

	account->DecreaseBalance(amount);
	mAccountRepository->AddOrUpdate(account);
	mAccountRepository->Save();

	Console::WriteLine("Income added!");
}

void SpendingMenu::Delete() const
{
	int id;
	Console::Write("Enter incoming transaction ID to delete: ");
	Console::ReadLine(id);

	SpendingTransaction* transaction = mSpendingTransactionRepository->GetById(id);

	if (transaction == nullptr)
	{
		Console::WriteLine("Incoming transaction with this ID not found!");
		return;
	}

	mSpendingTransactionRepository->Delete(transaction);
	mSpendingTransactionRepository->Save();

	Account* account = transaction->GetAccount();
	account->IncreaseBalance(transaction->GetAmount());
	mAccountRepository->AddOrUpdate(account);
	mAccountRepository->Save();

	Console::WriteLine("Income deleted!");
}

SpendingMenu::SpendingMenu(const shared_ptr<AccountRepository>& accountRepository,
	const shared_ptr<CategoryRepository>& categoryRepository, const shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository,
	const shared_ptr<CounterService>& counterService) : mAccountRepository(accountRepository), mCategoryRepository(categoryRepository),
	mSpendingTransactionRepository(spendingTransactionRepository), mCounterService(counterService)
{
}

void SpendingMenu::ShowMenu() const
{
	while (true)
	{
		Console::WriteLine("Choose spending action:");
		Console::WriteLine("1. List spendings");
		Console::WriteLine("2. Add spending");
		Console::WriteLine("3. Delete spending");
		Console::WriteLine("0. Back");
		Console::Write("Your choice: ");

		int choice;
		Console::ReadLine(choice);

		switch (choice)
		{
		case 1: List(); break;
		case 2: Add(); break;
		case 3: Delete(); break;
		case 0: return;
		default: Console::WriteLine("Incorrect choice. Try again."); continue;
		}

		system("pause");
	}
}