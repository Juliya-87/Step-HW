#pragma once

#include <iostream>





using namespace std;

class Date
{
	int day;
	int month;
	int year;

	char* strMonth;

public:

	//Date()
	//{
	//	cout << "Costructor  Date() " << endl;
	//}
	Date(int d, int m, int y)
	{
		cout << "Costructor  Date(int d, int m, int y) " << endl;
		day = d;
		month = m;
		year = y;
		strMonth = new char[4] {"Mon"};

		

	}

	Date(const Date& d)/////  copy  
	{
		day = d.day;
		month = d.month;
		year = d.year;

		////strMonth = d.strMonth; //// bit copy   поверхнева копія  за замовчуванням предоставляється системою  не підходить
	 
	 
		/////NO   приравнивание указателей
		strMonth = new char[4];
		strcpy_s(strMonth, 4, d.strMonth);

	}

	void Output() const;
	int GetDay()const { return day; };
	int GetMoth()const { return month; };
	int GetYear() const { return year; } ;


	void SetDay(int d);
	void SetMonth(int m);
	void SetYear(int y);
	~Date()
	{
		cout << "Destructor  ~Date() " << endl;
		delete[] strMonth;

	}



	void TestConst(Date& dt)const
	{
		//// this*  -----   вказівник на константу
	
		dt.day = 1;
		dt.month = 1;
		dt.year = 1;



	}


};