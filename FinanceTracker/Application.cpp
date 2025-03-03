#include "Application.h"

#include "Console.h"
#include "MainMenu.h"

void Application::Run()
{
	try
	{
		RegisterDependencies(mContainer);

		const std::shared_ptr<MainMenu> mainMenu = mContainer.Resolve<MainMenu>();
		mainMenu->ShowMenu();
	}
	catch (const std::exception& e)
	{
		Console::WriteLine("Error occured: ", e.what());
	}
	catch (...)
	{
		Console::WriteLine("Unknown error occurred.");
	}
}
