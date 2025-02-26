#pragma once
#include "MyString.h"
#include "Serializable.h"

template <typename T>
concept is_serializable = std::is_base_of_v<Serializable, T>;

template <is_serializable T>
class Serializer final
{
public:
	static MyString Serialize(T* object)
	{
		return object->ToString();
	}

	static T* Deserialize(MyString& str)
	{
		auto object = new T();
		object->Parse(str);

		return object;
	}
};
