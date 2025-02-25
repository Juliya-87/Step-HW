#pragma once
#include "AccountsMenu.h"
#include "CategoriesMenu.h"
#include "IncomeMenu.h"
#include "ReportsMenu.h"
#include "SpendingMenu.h"

class MainMenu
{
private:
	std::shared_ptr<AccountsMenu> mAccountsMenu;
	std::shared_ptr<CategoriesMenu> mCategoryMenu;
	std::shared_ptr<IncomeMenu> mIncomeMenu;
	std::shared_ptr<SpendingMenu> mSpendingMenu;
	std::shared_ptr<ReportsMenu> mReportsMenu;

public:
	MainMenu(const std::shared_ptr<AccountsMenu>& accountsMenu, const std::shared_ptr<CategoriesMenu>& categoriesMenu,
	         const std::shared_ptr<IncomeMenu>& incomeMenu, const std::shared_ptr<SpendingMenu>& spendingMenu,
	         const std::shared_ptr<ReportsMenu>& reportsMenu);

	void ShowMenu() const;
};
