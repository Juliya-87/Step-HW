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

template <is_class... T>
void RegisterStorageManagers(DIContainer& container)
{
	(container.Register<FileStorageManager<T>, FileHandler>(), ...);
	(container.Register<StorageManager<T>>([&container]() { return container.Resolve<FileStorageManager<T>>(); }), ...);
}

void RegisterDependencies(DIContainer& container)
{
	container.Register<CsvFileHandler>();
	container.Register<FileHandler>([&container]() { return container.Resolve<CsvFileHandler>(); });
	RegisterStorageManagers<Account, Category, Counter, IncomingTransaction, SpendingTransaction>(container);

	container.Register<IncomingTransactionRepository, StorageManager<IncomingTransaction>>();
	container.Register<SpendingTransactionRepository, StorageManager<SpendingTransaction>>();
	container.Register<AccountRepository, StorageManager<Account>, IncomingTransactionRepository, SpendingTransactionRepository>();
	container.Register<CategoryRepository, StorageManager<Category>, SpendingTransactionRepository>();
	container.Register<CounterRepository, StorageManager<Counter>>();

	const auto accountRepository = container.Resolve<AccountRepository>();
	const auto categoryRepository = container.Resolve<CategoryRepository>();
	const auto incomingTransactionRepository = container.Resolve<IncomingTransactionRepository>();
	const auto spendingTransactionRepository = container.Resolve<SpendingTransactionRepository>();

	incomingTransactionRepository->InitializeAccountRepository(accountRepository);
	spendingTransactionRepository->InitializeAccountRepository(accountRepository);
	spendingTransactionRepository->InitializeCategoryRepository(categoryRepository);

	container.Register<CounterService, CounterRepository>();
	container.Register<ReportDataSource, CategoryRepository, SpendingTransactionRepository>();

	container.Register<SpendingReport, ReportDataSource, FileHandler>();
	container.Register<CategoryReport, ReportDataSource, FileHandler>();
	container.Register<SpendingRating, ReportDataSource, FileHandler>();
	container.Register<CategoryRating, ReportDataSource, FileHandler>();

	container.Register<AccountsMenu, AccountRepository, CounterService>();
	container.Register<CategoriesMenu, CategoryRepository, CounterService>();
	container.Register<IncomeMenu, AccountRepository, IncomingTransactionRepository, CounterService>();
	container.Register<SpendingMenu, AccountRepository, CategoryRepository, SpendingTransactionRepository, CounterService>();
	container.Register<ReportsMenu, SpendingReport, CategoryReport, SpendingRating, CategoryRating>();
	container.Register<MainMenu, AccountsMenu, CategoriesMenu, IncomeMenu, SpendingMenu, ReportsMenu>();
}
