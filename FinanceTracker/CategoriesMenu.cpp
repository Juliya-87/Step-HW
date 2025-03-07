#include "CategoriesMenu.h"

#include "Console.h"

using namespace std;

CategoriesMenu::CategoriesMenu(const shared_ptr<CategoryRepository>& categoryRepository,
	const shared_ptr<CounterService>& counterService,
	const shared_ptr<StorageTransactionManager>& storageTransactionManager)
	: mCategoryRepository(categoryRepository), mCounterService(counterService),
	mStorageTransactionManager(storageTransactionManager)
{
}

void CategoriesMenu::ShowMenu() const
{
	while (true)
	{
		Console::WriteLine("Choose category action:");
		Console::WriteLine("1. List categories");
		Console::WriteLine("2. Add category");
		Console::WriteLine("3. Rename category");
		Console::WriteLine("4. Delete category");
		Console::WriteLine("0. Back");
		Console::Write("Your choice: ");

		int choice;
		Console::ReadLine(choice);

		switch (choice)
		{
		case 1: List(); break;
		case 2: Add(); break;
		case 3: Rename(); break;
		case 4: Delete(); break;
		case 0: return;
		default: Console::WriteLine("Incorrect choice. Try again."); continue;
		}

		Console::Pause();
	}
}

void CategoriesMenu::List() const
{
	const auto& categories = mCategoryRepository->GetAll();

	if (categories.empty()) {
		Console::WriteLine("No categories available.");
		return;
	}

	for (const auto& category : categories)
	{
		Console::WriteLine("ID: ", category->GetId(), ", Name: ", category->GetName());
	}
}

void CategoriesMenu::Add() const
{
	MyString name;
	Console::Write("Enter category name: ");
	Console::ReadLine(name);

	const auto storageTransaction = mStorageTransactionManager->BeginTransaction();

	const int id = mCounterService->GetNextCategoryId();
	auto newCategory = make_unique<Category>(id, name);
	mCategoryRepository->Add(std::move(newCategory));
	mCategoryRepository->Save();

	storageTransaction->Commit();

	Console::WriteLine("Category added!");
}

void CategoriesMenu::Rename() const
{
	int id;
	MyString newName;
	Console::Write("Enter category ID to rename: ");
	Console::ReadLine(id);

	const auto optionalCategory = mCategoryRepository->GetById(id);
	if (!optionalCategory.has_value())
	{
		Console::WriteLine("Category with this ID not found!");
		return;
	}

	Console::Write("Enter new name: ");
	Console::ReadLine(newName);

	Category* category = optionalCategory.value();
	category->Rename(newName);
	mCategoryRepository->Update(category);
	mCategoryRepository->Save();

	Console::WriteLine("Category name changed!");
}

void CategoriesMenu::Delete() const
{
	int id;
	Console::Write("Enter category ID to delete: ");
	Console::ReadLine(id);

	const auto optionalCategory = mCategoryRepository->GetById(id);
	if (!optionalCategory.has_value())
	{
		Console::WriteLine("Category with this ID not found!");
		return;
	}

	const Category* category = optionalCategory.value();
	if (mCategoryRepository->Delete(category))
	{
		mCategoryRepository->Save();
		Console::WriteLine("Category deleted!");
	}
	else
	{
		Console::WriteLine("Category is used in transactions. Unable to delete.");
	}
}
