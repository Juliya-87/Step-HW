#include "CategoriesMenu.h"

#include "Console.h"

using namespace std;

void CategoriesMenu::List() const
{
	const vector<Category*> categories = mCategoryRepository->GetAll();

	if (categories.empty()) {
		Console::WriteLine("No categories available.");
		return;
	}

	for (const Category* category : categories)
	{
		Console::WriteLine("ID: ", category->GetId(), ", Name: ", category->GetName().GetCStr());
	}
}

void CategoriesMenu::Add() const
{
	auto name = MyString();
	Console::Write("Enter category name: ");
	Console::ReadLine(name);

	const int id = mCounterService->GetNextCategoryId();

	const auto newCategory = new Category(id, name);
	mCategoryRepository->AddOrUpdate(newCategory);
	mCategoryRepository->Save();

	Console::WriteLine("Category added!");
}

void CategoriesMenu::Rename() const
{
	int id;
	MyString newName;
	Console::Write("Enter category ID to rename: ");
	Console::ReadLine(id);
	Console::Write("Enter new name: ");
	Console::ReadLine(newName);

	Category* category = mCategoryRepository->GetById(id);

	if (category == nullptr)
	{
		Console::WriteLine("Category with this ID not found!");
		return;
	}

	category->Rename(newName);
	mCategoryRepository->AddOrUpdate(category);
	mCategoryRepository->Save();

	Console::WriteLine("Category name changed!");
}

void CategoriesMenu::Delete() const
{
	int id;
	Console::Write("Enter category ID to delete: ");
	Console::ReadLine(id);

	Category* category = mCategoryRepository->GetById(id);

	if (category == nullptr)
	{
		Console::WriteLine("Category with this ID not found!");
		return;
	}

	if (mCategoryRepository->Delete(category))
	{
		mCategoryRepository->Save();
		Console::WriteLine("Category deleted!");
	}
	else
	{
		Console::WriteLine("Category is used in transactions. Can't delete!");
	}
}

CategoriesMenu::CategoriesMenu(const shared_ptr<CategoryRepository>& categoryRepository, const shared_ptr<CounterService>& counterService)
: mCategoryRepository(categoryRepository), mCounterService(counterService)
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

		system("pause");
	}
}
