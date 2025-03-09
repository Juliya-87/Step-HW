#pragma once
#include <functional>
#include <vector>

#include "MyString.h"
#include "FileStorageManager.h"

template <typename T>
concept is_model_based = requires { typename T::key_type; }&& std::derived_from<T, Model<typename T::key_type>>;

template <is_model_based T>
class Repository
{
public:
	virtual ~Repository() = default;

	std::vector<std::reference_wrapper<T>> GetAll()
	{
		EnsureInitialized();

		std::vector<std::reference_wrapper<T>> result;
		result.reserve(mItemsMap.size());

		for (const std::unique_ptr<T>& item : mItemsMap | std::views::values)
		{
			result.push_back(*item);
		}

		return result;
	}

	std::optional<std::reference_wrapper<T>> GetByKey(const typename T::key_type& key)
	{
		EnsureInitialized();

		const auto it = mItemsMap.find(key);

		if (it != mItemsMap.end())
		{
			return *it->second;
		}

		return std::nullopt;
	}

	std::vector<std::reference_wrapper<T>> GetByPredicate(const std::function<bool(const T&)>& predicate)
	{
		EnsureInitialized();

		std::vector<std::reference_wrapper<T>> result;

		for (const std::unique_ptr<T>& item : mItemsMap | std::views::values)
		{
			if (predicate(*item))
			{
				result.push_back(*item);
			}
		}

		return result;
	}

	void Add(std::unique_ptr<T> item)
	{
		EnsureInitialized();

		const auto it = mItemsMap.find(item->GetKey());

		if (it != mItemsMap.end())
		{
			throw std::runtime_error("Item already exists");
		}

		mItemsMap.emplace(item->GetKey(), std::move(item));
	}

	void Update(const T& item)
	{
		EnsureInitialized();

		const auto it = mItemsMap.find(item.GetKey());

		if (it == mItemsMap.end())
		{
			throw std::runtime_error("Item not found in repository");
		}

		if (it->second.get() == &item)
		{
			return;
		}

		*it->second = item;
	}

	bool Delete(const typename T::key_type& key)
	{
		EnsureInitialized();

		const auto it = mItemsMap.find(key);

		if (it != mItemsMap.end() && CanDeleteItem(*it->second))
		{
			mDeletedItems.push_back(std::move(it->second));
			mItemsMap.erase(it);
			return true;
		}

		return false;
	}

	virtual void Save()
	{
		if (!mIsInitialized)
		{
			return;
		}

		mStorageManager->Save(mTableName, GetAll());
		mDeletedItems.clear();
	}

protected:
	Repository(const MyString& tableName, const std::shared_ptr<StorageManager<T>>& storageManager)
		: mTableName(tableName), mStorageManager(storageManager)
	{
	}

	virtual void InitializeLoadedItem(T& item)
	{
	}

	virtual bool CanDeleteItem(const T& item)
	{
		return true;
	}

private:
	void EnsureInitialized()
	{
		std::call_once(mInitializedFlag, [this]()
			{
				auto items = mStorageManager->Load(mTableName);

				for (std::unique_ptr<T>& item : items)
				{
					InitializeLoadedItem(*item);
					mItemsMap.emplace(item->GetKey(), std::move(item));
				}

				mIsInitialized = true;
			});
	}

	MyString mTableName;
	std::shared_ptr<StorageManager<T>> mStorageManager;
	std::unordered_map<typename T::key_type, std::unique_ptr<T>> mItemsMap;
	std::vector<std::unique_ptr<T>> mDeletedItems;
	std::once_flag mInitializedFlag;
	bool mIsInitialized = false;
};
