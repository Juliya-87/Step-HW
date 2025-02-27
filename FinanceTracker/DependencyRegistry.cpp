#include "DependencyRegistry.h"

#include "AccountRepository.h"
#include "AccountsMenu.h"
#include "CategoriesMenu.h"
#include "CategoryRating.h"
#include "CategoryReport.h"
#include "CategoryRepository.h"
#include "CounterRepository.h"
#include "CounterService.h"
#include "IncomeMenu.h"
#include "IncomingTransactionRepository.h"
#include "MainMenu.h"
#include "ReportDataSource.h"
#include "ReportsMenu.h"
#include "SpendingMenu.h"
#include "SpendingRating.h"
#include "SpendingReport.h"
#include "SpendingTransactionRepository.h"

void RegisterDependencies(DIContainer& container)
{
	container.Register<IncomingTransactionRepository>();
	container.Register<SpendingTransactionRepository>();
	container.Register<AccountRepository, IncomingTransactionRepository, SpendingTransactionRepository>();
	container.Register<CategoryRepository, SpendingTransactionRepository>();
	container.Register<CounterRepository>();

	const std::shared_ptr<AccountRepository> accountRepository = container.Resolve<AccountRepository>();
	const std::shared_ptr<CategoryRepository> categoryRepository = container.Resolve<CategoryRepository>();
	const std::shared_ptr<IncomingTransactionRepository> incomingTransactionRepository = container.Resolve<IncomingTransactionRepository>();
	const std::shared_ptr<SpendingTransactionRepository> spendingTransactionRepository = container.Resolve<SpendingTransactionRepository>();

	incomingTransactionRepository->InitializeAccountRepository(accountRepository);
	spendingTransactionRepository->InitializeAccountRepository(accountRepository);
	spendingTransactionRepository->InitializeCategoryRepository(categoryRepository);

	container.Register<CounterService, CounterRepository>();
	container.Register<ReportDataSource, CategoryRepository, SpendingTransactionRepository>();

	container.Register<SpendingReport, ReportDataSource>();
	container.Register<CategoryReport, ReportDataSource>();
	container.Register<SpendingRating, ReportDataSource>();
	container.Register<CategoryRating, ReportDataSource>();

	container.Register<AccountsMenu, AccountRepository, CounterService>();
	container.Register<CategoriesMenu, CategoryRepository, CounterService>();
	container.Register<IncomeMenu, AccountRepository, IncomingTransactionRepository, CounterService>();
	container.Register<SpendingMenu, AccountRepository, CategoryRepository, SpendingTransactionRepository, CounterService>();
	container.Register<ReportsMenu, SpendingReport, CategoryReport, SpendingRating, CategoryRating>();
	container.Register<MainMenu, AccountsMenu, CategoriesMenu, IncomeMenu, SpendingMenu, ReportsMenu>();
}
