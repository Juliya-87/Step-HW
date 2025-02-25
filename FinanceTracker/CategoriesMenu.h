#pragma once
#include "CategoryRepository.h"
#include "CounterService.h"

class CategoriesMenu
{
private:
	std::shared_ptr<CategoryRepository> mCategoryRepository = nullptr;
	std::shared_ptr<CounterService> mCounterService = nullptr;

	void List() const;
	void Add() const;
	void Rename() const;
	void Delete() const;

public:
	CategoriesMenu(const std::shared_ptr<CategoryRepository>& categoryRepository, const std::shared_ptr<CounterService>& counterService);

	void ShowMenu() const;
};

