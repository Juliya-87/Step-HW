#pragma once
#include "DependencyRegistry.h"

class Application
{
public:
	void Run();

private:
	DIContainer mContainer;
};
