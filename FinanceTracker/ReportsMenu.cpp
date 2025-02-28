#include "ReportsMenu.h"

#include "Console.h"
#include "ConversionHelpers.h"

using namespace std;

void ReportsMenu::PrintReport(const Report* report)
{
	if (!report)
	{
		Console::WriteLine("Invalid report.");
		return;
	}

	int period;
	Console::Write("Enter period (1 - Day, 2 - Week, 3 - Month): ");
	Console::ReadLine(period);

	const auto reportingPeriod = IntToReportingPeriod(period);
	if (reportingPeriod == UNDEFINED)
	{
		Console::WriteLine("Incorrect choice. Try again.");
		return;
	}

	int action;
	Console::Write("Enter action (1 - Print, 2 - Export): ");
	Console::ReadLine(action);

	switch (action)
	{
	case 1: report->Print(reportingPeriod); break;
	case 2: report->Export(reportingPeriod); break;
	default: Console::WriteLine("Incorrect choice. Try again."); break;
	}
}

ReportsMenu::ReportsMenu(const shared_ptr<SpendingReport>& spendingReport, const shared_ptr<CategoryReport>& categoryReport,
	const shared_ptr<SpendingRating>& spendingRating, const shared_ptr<CategoryRating>& categoryRating)
	: mSpendingReport(spendingReport), mCategoryReport(categoryReport),
	mSpendingRating(spendingRating), mCategoryRating(categoryRating)
{
}

void ReportsMenu::ShowMenu() const
{
	while (true)
	{
		Console::WriteLine("Choose income action:");
		Console::WriteLine("1. Spending report");
		Console::WriteLine("2. Category report");
		Console::WriteLine("3. Spending rating");
		Console::WriteLine("4. Category rating");
		Console::WriteLine("0. Back");
		Console::Write("Your choice: ");

		int choice;
		Console::ReadLine(choice);

		switch (choice)
		{
		case 1: PrintReport(mSpendingReport.get()); break;
		case 2: PrintReport(mCategoryReport.get()); break;
		case 3: PrintReport(mSpendingRating.get()); break;
		case 4: PrintReport(mCategoryRating.get()); break;
		case 0: return;
		default: Console::WriteLine("Incorrect choice. Try again."); continue;
		}

		system("pause");
	}
}
