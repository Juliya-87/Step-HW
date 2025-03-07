#include "Application.h"

#include "Console.h"
#include "MainMenu.h"

using namespace std;

void Application::Run()
{
	try
	{
		RegisterDependencies(mContainer);

		const shared_ptr<MainMenu> mainMenu = mContainer.Resolve<MainMenu>();
		mainMenu->ShowMenu();
	}
	catch (const exception& e)
	{
		Console::WriteLine("Error occured: ", e.what());
	}
	catch (...)
	{
		Console::WriteLine("Unknown error occurred.");
	}
}
