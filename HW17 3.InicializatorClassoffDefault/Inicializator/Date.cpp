#include "Date.h"

void Date::Output() const
{
	cout << day << " / " << month << " / " << year << endl;
}






void Date::SetDay(int d)
{
	day = d;
}

void Date::SetMonth(int m)
{
	month = m;
}

void Date::SetYear(int y)
{
	year = y;
}
