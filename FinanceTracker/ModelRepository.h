#pragma once
#include "ModelBase.h"
#include "Repository.h"

template <typename T>
concept is_model_base = std::is_base_of_v<ModelBase, T>;

template <is_model_base T>
class ModelRepository : public Repository<T>
{
public:
	T* GetById(const int id)
	{
		const std::vector<T*> items = this->GetAll();

		for (T* item : items)
		{
			if (item->GetId() == id)
			{
				return item;
			}
		}

		return nullptr;
	}
};
