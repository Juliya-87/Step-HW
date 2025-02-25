#pragma once
#include "MyString.h"
#include "Serializable.h"

template <typename T>
class Serializer final
{
public:
	static MyString Serialize(T* object)
	{
		return static_cast<Serializable*>(object)->ToString();
	}

	static T* Deserialize(MyString& str)
	{
		auto object = static_cast<Serializable*>(new T());
		object->Parse(str);

		return static_cast<T*>(object);
	}
};
