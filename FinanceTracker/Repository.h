#pragma once
#include <vector>
#include <fstream>
#include <string>

#include "Console.h"
#include "MyString.h"
#include "Serializer.h"

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
		EnsureItemsInitialized();

		isInitialized = true;
	}

	void EnsureItemsInitialized()
	{
		std::ifstream file(mFullFileName.GetCStr());
		if (!file.is_open())
		{
			Console::WriteLine("Unable to open the file ", mFullFileName.GetCStr());
			return;
		}

		std::string line;

		while (getline(file, line)) {
			auto str = MyString(line.c_str());
			T* item = Serializer<T>::Deserialize(str);
			AfterDeserialized(item);
			mItems.push_back(item);
		}

		file.close();
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

		std::ofstream file(mFullFileName.GetCStr());
		if (!file.is_open())
		{
			Console::WriteLine("Unable to open the file ", mFullFileName.GetCStr());
			return;
		}

		for (T* item : mItems)
		{
			const MyString line = Serializer<T>::Serialize(item);
			file << line.GetCStr() << '\n';
		}

		file.close();
	}

	virtual ~Repository()
	{
		for (const T* item : mItems) {
			delete item;
		}

		mItems.clear();
	}
};
