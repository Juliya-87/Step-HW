#pragma once
#include "ModelBase.h"
#include "Repository.h"

template <typename T>
concept is_model_base = std::is_base_of_v<ModelBase, T>;

template <is_model_base T>
class ModelRepository : public Repository<T>
{
protected:
	ModelRepository(const std::shared_ptr<StorageManager<T>>& storageManager) : Repository<T>(storageManager)
	{
	}

public:
	T* GetById(const int id)
	{
		const std::vector<std::unique_ptr<T>>& items = this->GetAll();

		for (const auto& item : items)
		{
			if (item->GetId() == id)
			{
				return item.get();
			}
		}

		return nullptr;
	}
};
