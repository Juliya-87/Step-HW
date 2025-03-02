#include "SpendingMenu.h"

#include "AccountRepository.h"
#include "CategoryRepository.h"
#include "Console.h"
#include "ConversionHelpers.h"

using namespace std;

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

		Console::Pause();
	}
}

void SpendingMenu::List() const
{
	const auto& transactions = mSpendingTransactionRepository->GetAll();

	if (transactions.empty()) {
		Console::WriteLine("No spending transactions available.");
		return;
	}

	for (const auto& transaction : transactions)
	{
		Console::WriteLine("ID: ", transaction->GetId(),
			", Account: ", transaction->GetAccount()->GetName(),
			", Amount: ", ToString(transaction->GetAmount(), 2),
			", Category: ", transaction->GetCategory()->GetName(),
			", Notes: ", transaction->GetNotes(),
			", Time: ", ToString(transaction->GetTransactionTime()));
	}
}

void SpendingMenu::Add() const
{
	double amount;
	int accountId;
	int categoryId;
	MyString notes;
	Console::WriteLine("Choose account for the transaction:");
	for (const auto& account : mAccountRepository->GetAll())
	{
		Console::WriteLine(account->GetId(), ". ", account->GetName());
	}
	Console::Write("Your choice: ");
	Console::ReadLine(accountId);

	const auto optionalAccount = mAccountRepository->GetById(accountId);
	if (!optionalAccount.has_value())
	{
		Console::WriteLine("Account with this ID not found!");
		return;
	}

	Console::WriteLine("Choose category for the transaction:");
	for (const auto& category : mCategoryRepository->GetAll())
	{
		Console::WriteLine(category->GetId(), ". ", category->GetName());
	}
	Console::Write("Your choice: ");
	Console::ReadLine(categoryId);

	const auto optionalCategory = mCategoryRepository->GetById(categoryId);
	if (!optionalCategory.has_value())
	{
		Console::WriteLine("Category with this ID not found!");
		return;
	}

	Console::Write("Enter spending amount: ");
	Console::ReadLine(amount);
	Console::Write("Enter notes: ");
	Console::ReadLine(notes);

	const int id = mCounterService->GetNextTransactionId();
	Account* account = optionalAccount.value();
	Category* category = optionalCategory.value();

	auto newTransaction = make_unique<SpendingTransaction>(id, amount, account, category, notes);
	mSpendingTransactionRepository->Add(std::move(newTransaction));
	mSpendingTransactionRepository->Save();

	account->DecreaseBalance(amount);
	mAccountRepository->Update(account);
	mAccountRepository->Save();

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

	const SpendingTransaction* transaction = optionalTransaction.value();

	Account* account = transaction->GetAccount();
	account->IncreaseBalance(transaction->GetAmount());
	mAccountRepository->Update(account);
	mAccountRepository->Save();

	mSpendingTransactionRepository->Delete(transaction);
	mSpendingTransactionRepository->Save();

	Console::WriteLine("Spending deleted!");
}
