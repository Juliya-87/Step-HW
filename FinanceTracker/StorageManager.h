#pragma once
#include "MyString.h"
#include "Serializable.h"

template <typename T>
concept is_serializable = std::is_base_of_v<Serializable, T>;

template <is_serializable T>
class StorageManager
{
public:
	virtual ~StorageManager() = default;

	virtual void Save(const MyString& tableName, const std::vector<std::reference_wrapper<T>>& items) = 0;
	virtual std::vector<std::unique_ptr<T>> Load(const MyString& tableName) = 0;
};
