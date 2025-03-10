#include "SpendingMenu.h"

#include "AccountRepository.h"
#include "CategoryRepository.h"
#include "Console.h"
#include "ConversionHelpers.h"

using namespace std;

SpendingMenu::SpendingMenu(const shared_ptr<AccountRepository>& accountRepository,
	const shared_ptr<CategoryRepository>& categoryRepository,
	const shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository,
	const shared_ptr<CounterService>& counterService,
	const shared_ptr<StorageTransactionManager>& storageTransactionManager)
	: mAccountRepository(accountRepository), mCategoryRepository(categoryRepository),
	mSpendingTransactionRepository(spendingTransactionRepository), mCounterService(counterService),
	mStorageTransactionManager(storageTransactionManager)
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

		Console::Pause();
	}
}

void SpendingMenu::List() const
{
	const auto transactions = mSpendingTransactionRepository->GetAll();

	if (transactions.empty())
	{
		Console::WriteLine("No spending transactions available.");
		return;
	}

	for (const SpendingTransaction& transaction : transactions | views::transform(&reference_wrapper<SpendingTransaction>::get))
	{
		Console::WriteLine("ID: ", transaction.GetId(),
			", Account: ", transaction.GetAccount().GetName(),
			", Amount: ", ToString(transaction.GetAmount(), 2),
			", Category: ", transaction.GetCategory().GetName(),
			", Notes: ", transaction.GetNotes(),
			", Time: ", ToString(transaction.GetTransactionTime()));
	}
}

void SpendingMenu::Add() const
{
	double amount;
	int accountId;
	int categoryId;
	MyString notes;
	Console::WriteLine("Choose account for the transaction:");
	for (const Account& account : mAccountRepository->GetAll() | views::transform(&reference_wrapper<Account>::get))
	{
		Console::WriteLine(account.GetId(), ". ", account.GetName());
	}
	Console::Write("Your choice: ");
	Console::ReadLine(accountId);

	const auto optionalAccount = mAccountRepository->GetById(accountId);
	if (!optionalAccount.has_value())
	{
		Console::WriteLine("Account with this ID not found!");
		return;
	}

	Account& account = optionalAccount.value();

	Console::WriteLine("Choose category for the transaction:");
	for (const Category& category : mCategoryRepository->GetAll() | views::transform(&reference_wrapper<Category>::get))
	{
		Console::WriteLine(category.GetId(), ". ", category.GetName());
	}
	Console::Write("Your choice: ");
	Console::ReadLine(categoryId);

	const auto optionalCategory = mCategoryRepository->GetById(categoryId);
	if (!optionalCategory.has_value())
	{
		Console::WriteLine("Category with this ID not found!");
		return;
	}

	Category& category = optionalCategory.value();

	Console::Write("Enter spending amount: ");
	Console::ReadLine(amount);
	Console::Write("Enter notes: ");
	Console::ReadLine(notes);

	const auto storageTransaction = mStorageTransactionManager->BeginTransaction();

	const int id = mCounterService->GetNextTransactionId();
	auto newTransaction = make_unique<SpendingTransaction>(id, amount, account, category, notes);
	mSpendingTransactionRepository->Add(std::move(newTransaction));

	account.DecreaseBalance(amount);
	mAccountRepository->Update(account);

	mSpendingTransactionRepository->Save();
	mAccountRepository->Save();

	storageTransaction->Commit();

	Console::WriteLine("Spending added!");
}

void SpendingMenu::Delete() const
{
	int id;
	Console::Write("Enter spending transaction ID to delete: ");
	Console::ReadLine(id);

	const auto optionalTransaction = mSpendingTransactionRepository->GetById(id);
	if (!optionalTransaction.has_value())
	{
		Console::WriteLine("Spending transaction with this ID not found!");
		return;
	}

	const SpendingTransaction& transaction = optionalTransaction.value();

	const auto storageTransaction = mStorageTransactionManager->BeginTransaction();

	mSpendingTransactionRepository->Delete(transaction.GetId());

	Account& account = transaction.GetAccount();
	account.IncreaseBalance(transaction.GetAmount());
	mAccountRepository->Update(account);

	mSpendingTransactionRepository->Save();
	mAccountRepository->Save();

	storageTransaction->Commit();

	Console::WriteLine("Spending deleted!");
}
