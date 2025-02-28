// FinanceTracker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "DependencyRegistry.h"
#include "DIContainer.h"
#include "MainMenu.h"

int main()
{
	DIContainer container;
	RegisterDependencies(container);

	const std::shared_ptr<MainMenu> mainMenu = container.Resolve<MainMenu>();
	mainMenu->ShowMenu();

	return 0;
}
