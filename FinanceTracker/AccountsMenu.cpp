#include "AccountsMenu.h"

#include "Console.h"
#include "ConversionHelpers.h"

using namespace std;

void AccountsMenu::List() const
{
	const auto& accounts = mAccountRepository->GetAll();

	if (accounts.empty()) {
		Console::WriteLine("No accounts available.");
		return;
	}

	for (const auto& account : accounts)
	{
		Console::WriteLine("ID: ", account->GetId(),
			", Name: ", account->GetName(),
			", Type: ", ToString(account->GetType()),
			", Balance: ", ToString(account->GetBalance(), 2));
	}
}

void AccountsMenu::Add() const
{
	MyString name;
	int type;
	Console::Write("Enter account name: ");
	Console::ReadLine(name);
	Console::Write("Enter account type (1 - ", ToString(CREDIT_CARD),
		", 2 - ", ToString(DEBIT_CARD),
		", 3 - ", ToString(WALLET), "): ");
	Console::ReadLine(type);

	const AccountType accountType = IntToAccountType(type);
	if (accountType == NONE)
	{
		Console::WriteLine("Incorrect choice of the type. Try again.");
		return;
	}

	const int id = mCounterService->GetNextAccountId();

	auto newAccount = make_unique<Account>(id, name, accountType);
	mAccountRepository->Add(std::move(newAccount));
	mAccountRepository->Save();

	Console::WriteLine("Account added!");
}

void AccountsMenu::Rename() const
{
	int id;
	MyString newName;
	Console::Write("Enter account ID to rename: ");
	Console::ReadLine(id);
	Console::Write("Enter new name: ");
	Console::ReadLine(newName);

	Account* account = mAccountRepository->GetById(id);

	if (account == nullptr)
	{
		Console::WriteLine("Account with this ID not found!");
		return;
	}

	account->Rename(newName);
	mAccountRepository->Update(account);
	mAccountRepository->Save();

	Console::WriteLine("Account name changed!");
}

void AccountsMenu::ChangeType() const
{
	int id;
	int newType;
	Console::Write("Enter account ID to rename: ");
	Console::ReadLine(id);
	Console::Write("Enter new type (1 - ", ToString(CREDIT_CARD),
		", 2 - ", ToString(DEBIT_CARD),
		", 3 - ", ToString(WALLET), "): ");
	Console::ReadLine(newType);

	const AccountType newAccountType = IntToAccountType(newType);
	if (newAccountType == NONE)
	{
		Console::WriteLine("Incorrect choice of the type. Try again.");
		return;
	}

	Account* account = mAccountRepository->GetById(id);

	if (account == nullptr)
	{
		Console::WriteLine("Account with this ID not found!");
		return;
	}

	account->ChangeType(newAccountType);
	mAccountRepository->Update(account);
	mAccountRepository->Save();

	Console::WriteLine("Account type changed!");
}

void AccountsMenu::Delete() const
{
	int id;
	Console::Write("Enter account ID to delete: ");
	Console::ReadLine(id);

	const Account* account = mAccountRepository->GetById(id);

	if (account == nullptr)
	{
		Console::WriteLine("Account with this ID not found!");
		return;
	}

	if (mAccountRepository->Delete(account))
	{
		mAccountRepository->Save();
		Console::WriteLine("Account deleted!");
	}
	else
	{
		Console::WriteLine("Account is used in transactions. Unable to delete.");
	}
}

AccountsMenu::AccountsMenu(const shared_ptr<AccountRepository>& accountRepository, const shared_ptr<CounterService>& counterService)
	: mAccountRepository(accountRepository), mCounterService(counterService)
{
}

void AccountsMenu::ShowMenu() const
{
	while (true)
	{
		Console::WriteLine("Choose account action:");
		Console::WriteLine("1. List accounts");
		Console::WriteLine("2. Add account");
		Console::WriteLine("3. Rename account");
		Console::WriteLine("4. Change account type");
		Console::WriteLine("5. Delete account");
		Console::WriteLine("0. Back");
		Console::Write("Your choice: ");

		int choice;
		Console::ReadLine(choice);

		switch (choice)
		{
		case 1: List(); break;
		case 2: Add(); break;
		case 3: Rename(); break;
		case 4: ChangeType(); break;
		case 5: Delete(); break;
		case 0: return;
		default: Console::WriteLine("Incorrect choice. Try again."); continue;
		}

		system("pause");
	}
}
