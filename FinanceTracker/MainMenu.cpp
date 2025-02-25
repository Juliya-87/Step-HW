#include "MainMenu.h"

#include "Console.h"

using namespace std;

MainMenu::MainMenu(const shared_ptr<AccountsMenu>& accountsMenu, const shared_ptr<CategoriesMenu>& categoriesMenu,
	const shared_ptr<IncomeMenu>& incomeMenu, const shared_ptr<SpendingMenu>& spendingMenu,
	const shared_ptr<ReportsMenu>& reportsMenu)
	: mAccountsMenu(accountsMenu), mCategoryMenu(categoriesMenu),
	mIncomeMenu(incomeMenu), mSpendingMenu(spendingMenu),
	mReportsMenu(reportsMenu)
{
}

void MainMenu::ShowMenu() const
{
	while (true)
	{
		Console::WriteLine("Choose an action:");
		Console::WriteLine("1. Manage Accounts");
		Console::WriteLine("2. Manage Categories");
		Console::WriteLine("3. Manage Income");
		Console::WriteLine("4. Manage Spending");
		Console::WriteLine("5. Reports");
		Console::WriteLine("0. Exit");
		Console::Write("Your choice: ");

		int choice;
		Console::ReadLine(choice);

		switch (choice)
		{
		case 1:
			mAccountsMenu->ShowMenu();
			break;
		case 2:
			mCategoryMenu->ShowMenu();
			break;
		case 3:
			mIncomeMenu->ShowMenu();
			break;
		case 4:
			mSpendingMenu->ShowMenu();
			break;
		case 5:
			mReportsMenu->ShowMenu();
			break;
		case 0: return;
		default: Console::WriteLine("Incorrect choice. Try again.");
		}
	}
}
