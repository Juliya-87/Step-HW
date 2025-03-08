#pragma once
#include <vector>

#include "MyString.h"
#include "FileStorageManager.h"

template <is_serializable T>
class Repository
{
public:
	virtual ~Repository() = default;

	const std::vector<std::unique_ptr<T>>& GetAll()
	{
		EnsureInitialized();

		return mItems;
	}

	void Add(std::unique_ptr<T> item)
	{
		EnsureInitialized();

		for (const auto& vectorItem : mItems)
		{
			if (*vectorItem == *item)
			{
				throw std::runtime_error("Item already exists");
			}
		}

		mItems.push_back(std::move(item));
	}

	void Update(T* item)
	{
		EnsureInitialized();

		for (auto& vectorItem : mItems)
		{
			if (*vectorItem == *item)
			{
				if (vectorItem.get() == item)
				{
					return;
				}

				*vectorItem = *item;
				return;
			}
		}

		throw std::runtime_error("Item not found in repository");
	}

	bool Delete(const T* item)
	{
		EnsureInitialized();

		if (IsItemUsedInOtherRepository(item))
		{
			return false;
		}

		auto it = std::find_if(mItems.begin(), mItems.end(),
			[&](const std::unique_ptr<T>& vectorItem) { return *vectorItem == *item; });

		if (it != mItems.end())
		{
			mDeletedItems.push_back(std::move(*it));
			mItems.erase(it);
			return true;
		}

		return false;
	}

	virtual void Save()
	{
		if (!isInitialized)
		{
			return;
		}

		mStorageManager->Save(mTableName, mItems);
		mDeletedItems.clear();
	}

protected:
	Repository(const std::shared_ptr<StorageManager<T>>& storageManager) : mStorageManager(storageManager)
	{
	}

	virtual MyString GetTableName() = 0;

	virtual void AfterDeserialized(T* item)
	{
	}

	virtual bool IsItemUsedInOtherRepository(const T* item)
	{
		return false;
	}

private:
	void EnsureInitialized()
	{
		if (isInitialized)
		{
			return;
		}

		mTableName = GetTableName();
		mItems = mStorageManager->Load(mTableName);

		for (const auto& item : mItems)
		{
			AfterDeserialized(item.get());
		}

		isInitialized = true;
	}

	std::shared_ptr<StorageManager<T>> mStorageManager;
	MyString mTableName;
	std::vector<std::unique_ptr<T>> mItems;
	std::vector<std::unique_ptr<T>> mDeletedItems;
	bool isInitialized = false;
};
