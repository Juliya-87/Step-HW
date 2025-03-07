#pragma once
#include "CategoryRepository.h"
#include "CounterService.h"
#include "StorageTransactionManager.h"

class CategoriesMenu
{
public:
	CategoriesMenu(const std::shared_ptr<CategoryRepository>& categoryRepository,
		const std::shared_ptr<CounterService>& counterService,
		const std::shared_ptr<StorageTransactionManager>& storageTransactionManager);

	void ShowMenu() const;

private:
	void List() const;
	void Add() const;
	void Rename() const;
	void Delete() const;

	std::shared_ptr<CategoryRepository> mCategoryRepository;
	std::shared_ptr<CounterService> mCounterService;
	std::shared_ptr<StorageTransactionManager> mStorageTransactionManager;
};
