#pragma once
#include "ModelBase.h"
#include "Repository.h"

template <typename T>
class ModelRepository : public Repository<T>
{
public:
	T* GetById(const int id)
	{
		const std::vector<T*> items = this->GetAll();

		for (T* item : items)
		{
			const int itemId = static_cast<ModelBase*>(item)->GetId();
			if (itemId == id)
			{
				return item;
			}
		}

		return nullptr;
	}
};
