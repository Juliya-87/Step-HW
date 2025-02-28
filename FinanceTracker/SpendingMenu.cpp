#include "SpendingMenu.h"

#include "AccountRepository.h"
#include "CategoryRepository.h"
#include "Console.h"
#include "ConversionHelpers.h"

using namespace std;

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
	Console::WriteLine("Choose category for the transaction:");
	for (const auto& category : mCategoryRepository->GetAll())
	{
		Console::WriteLine(category->GetId(), ". ", category->GetName());
	}
	Console::Write("Your choice: ");
	Console::ReadLine(categoryId);
	Console::Write("Enter spending amount: ");
	Console::ReadLine(amount);
	Console::Write("Enter notes: ");
	Console::ReadLine(notes);

	const int id = mCounterService->GetNextTransactionId();
	Account* account = mAccountRepository->GetById(accountId);
	Category* category = mCategoryRepository->GetById(categoryId);

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

	const SpendingTransaction* transaction = mSpendingTransactionRepository->GetById(id);

	if (transaction == nullptr)
	{
		Console::WriteLine("Spending transaction with this ID not found!");
		return;
	}

	mSpendingTransactionRepository->Delete(transaction);
	mSpendingTransactionRepository->Save();

	Account* account = transaction->GetAccount();
	account->IncreaseBalance(transaction->GetAmount());
	mAccountRepository->Update(account);
	mAccountRepository->Save();

	Console::WriteLine("Spending deleted!");
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