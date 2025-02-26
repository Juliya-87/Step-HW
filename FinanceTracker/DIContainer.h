#pragma once
#include <functional>
#include <memory>
#include <stdexcept>
#include <typeindex>

template <typename T>
concept is_class = std::is_class_v<T>;

class DIContainer
{
private:
	std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>> factories;
	std::unordered_map<std::type_index, std::shared_ptr<void>> instances;

public:
	template <is_class T, is_class... Dependencies>
	void Register()
	{
		factories[typeid(T)] = [this]() { return std::make_shared<T>(Resolve<Dependencies>()...); };
	}

	template <is_class T>
	std::shared_ptr<T> Resolve()
	{
		const std::type_index typeIndex = typeid(T);

		if (instances.contains(typeIndex))
		{
			return std::static_pointer_cast<T>(instances[typeIndex]);
		}

		if (factories.contains(typeIndex))
		{
			auto instance = std::static_pointer_cast<T>(factories[typeIndex]());
			instances[typeIndex] = instance;
			return instance;
		}

		throw std::runtime_error("Type not registered in container");
	}
};
