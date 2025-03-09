#pragma once
#include <optional>

#include "ModelWithId.h"
#include "Repository.h"

template <typename T>
concept is_model_with_id_based = std::is_base_of_v<ModelWithId, T>;

template <is_model_with_id_based T>
class ModelWithIdRepository : public Repository<T>
{
public:
	std::optional<std::reference_wrapper<T>> GetById(const int id)
	{
		return this->GetByKey(id);
	}

protected:
	ModelWithIdRepository(const MyString& tableName, const std::shared_ptr<StorageManager<T>>& storageManager) : Repository<T>(tableName, storageManager)
	{
	}
};
