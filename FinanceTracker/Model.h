#pragma once
#include "Serializable.h"

template <typename T>
concept is_fundamental_type = std::is_fundamental_v<T> || std::is_same_v<T, MyString>;

template <is_fundamental_type T>
class Model : Serializable
{
public:
	using key_type = T;

	Model& operator=(const Model& other) = default;

	bool operator==(const Model& other) const
	{
		return GetKey() == other.GetKey();
	}

	virtual T GetKey() const = 0;

protected:
	Model() = default;
};
