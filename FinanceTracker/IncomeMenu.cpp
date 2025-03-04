#include "IncomeMenu.h"

#include "Console.h"
#include "ConversionHelpers.h"

using namespace std;

IncomeMenu::IncomeMenu(const shared_ptr<AccountRepository>& accountRepository,
	const shared_ptr<IncomingTransactionRepository>& incomingTransactionRepository,
	const shared_ptr<CounterService>& counterService) : mAccountRepository(accountRepository),
	mIncomingTransactionRepository(incomingTransactionRepository), mCounterService(counterService)
{
}

void IncomeMenu::ShowMenu() const
{
	while (true)
	{
		Console::WriteLine("Choose income action:");
		Console::WriteLine("1. List incomes");
		Console::WriteLine("2. Add income");
		Console::WriteLine("3. Delete income");
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

void IncomeMenu::List() const
{
	const auto& transactions = mIncomingTransactionRepository->GetAll();

	if (transactions.empty()) {
		Console::WriteLine("No incoming transactions available.");
		return;
	}

	for (const auto& transaction : transactions)
	{
		Console::WriteLine("ID: ", transaction->GetId(),
			", Account: ", transaction->GetAccount()->GetName(),
			", Amount: ", ToString(transaction->GetAmount(), 2),
			", Notes: ", transaction->GetNotes(),
			", Time: ", ToString(transaction->GetTransactionTime()));
	}
}

void IncomeMenu::Add() const
{
	double amount;
	int accountId;
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

	Console::Write("Enter income amount: ");
	Console::ReadLine(amount);
	Console::Write("Enter notes: ");
	Console::ReadLine(notes);

	Account* account = optionalAccount.value();
	const int id = mCounterService->GetNextTransactionId();

	auto newTransaction = make_unique<IncomingTransaction>(id, amount, account, notes);
	mIncomingTransactionRepository->Add(std::move(newTransaction));
	mIncomingTransactionRepository->Save();

	account->IncreaseBalance(amount);
	mAccountRepository->Update(account);
	mAccountRepository->Save();

	Console::WriteLine("Income added!");
}

void IncomeMenu::Delete() const
{
	int id;
	Console::Write("Enter incoming transaction ID to delete: ");
	Console::ReadLine(id);

	const auto optionalTransaction = mIncomingTransactionRepository->GetById(id);
	if (!optionalTransaction.has_value())
	{
		Console::WriteLine("Incoming transaction with this ID not found!");
		return;
	}

	const IncomingTransaction* transaction = optionalTransaction.value();

	Account* account = transaction->GetAccount();
	account->DecreaseBalance(transaction->GetAmount());
	mAccountRepository->Update(account);
	mAccountRepository->Save();

	mIncomingTransactionRepository->Delete(transaction);
	mIncomingTransactionRepository->Save();

	Console::WriteLine("Income deleted!");
}
