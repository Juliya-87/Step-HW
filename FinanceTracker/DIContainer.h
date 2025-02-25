#pragma once
#include <functional>
#include <memory>
#include <stdexcept>
#include <typeindex>

class DIContainer
{
private:
	std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>> factories;
	std::unordered_map<std::type_index, std::shared_ptr<void>> instances;

public:
	template <typename T, typename... Dependencies>
	void Register()
	{
		const std::type_index typeIndex = typeid(T);
		factories[typeIndex] = [this]() { return std::make_shared<T>(Resolve<Dependencies>()...); };
	}

	template <typename T>
	std::shared_ptr<T> Resolve()
	{
		const std::type_index typeIndex = typeid(T);
		const auto it = instances.find(typeIndex);
		if (it != instances.end())
		{
			return std::static_pointer_cast<T>(it->second);
		}
		const auto factoryIt = factories.find(typeIndex);
		if (factoryIt != factories.end()) {
			auto instance = std::static_pointer_cast<T>(factoryIt->second());
			instances[typeIndex] = instance;
			return instance;
		}
		throw std::runtime_error("Type not registered in container");
	}
};
