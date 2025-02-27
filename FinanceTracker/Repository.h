#pragma once
#include <vector>

#include "Console.h"
#include "MyString.h"
#include "CsvStorageManager.h"

template <is_serializable T>
class Repository
{
private:
	static constexpr char BASE_DIRECTORY[] = "Data";
	MyString mFullFileName;
	std::vector<T*> mItems;
	bool isInitialized = false;

	void EnsureInitialized()
	{
		if (isInitialized)
		{
			return;
		}

		EnsureFullFileNameInitialized();
		CsvStorageManager<T>::LoadFromCsv(mFullFileName, mItems);

		for (T* item : mItems)
		{
			AfterDeserialized(item);
		}

		isInitialized = true;
	}

	void EnsureFullFileNameInitialized()
	{
		const MyString fileName = GetFileName();

		mFullFileName = MyString(BASE_DIRECTORY);
		mFullFileName.Append("\\");
		mFullFileName.Append(fileName);
	}

protected:
	Repository() = default;

	virtual MyString GetFileName() = 0;

	virtual void AfterDeserialized(T* item)
	{
	}

	virtual bool IsItemUsedInOtherRepository(T* item)
	{
		return true;
	}

public:
	const std::vector<T*>& GetAll()
	{
		EnsureInitialized();

		return mItems;
	}

	void AddOrUpdate(T* item)
	{
		EnsureInitialized();

		const size_t size = mItems.size();
		for (size_t i = 0; i < size; i++)
		{
			T* vectorItem = mItems.at(i);
			if (*vectorItem == *item)
			{
				if (vectorItem == item)
				{
					return;
				}

				mItems.at(i) = item;
				delete vectorItem;
				return;
			}
		}

		mItems.push_back(item);
	}

	bool Delete(T* item)
	{
		EnsureInitialized();

		if (IsItemUsedInOtherRepository(item))
		{
			return false;
		}

		const size_t size = mItems.size();
		for (size_t i = 0; i < size; i++)
		{
			T* vectorItem = mItems.at(i);
			if (*vectorItem == *item)
			{
				mItems.erase(mItems.begin() + i);
				delete vectorItem;
				return true;
			}
		}

		return false;
	}

	virtual void Save()
	{
		if (!isInitialized)
		{
			return;
		}

		CsvStorageManager<T>::SaveToCsv(mFullFileName, mItems);
	}

	virtual ~Repository()
	{
		for (const T* item : mItems) {
			delete item;
		}

		mItems.clear();
	}
};
