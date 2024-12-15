#pragma once


#include "Date.h"
#include <iostream>
using namespace std;


class DrivigCards
{
	const double max_speed;
	int numb_speed_over;
	

	Date dat;//// очікується конструктор за замовчуванням, а його нема, тому треба ініціалізатор який на момент створення подасть параметри в конструктор з параметрами
	Person&  owner;   ///  ссылка на внешний обьект владельца карты  ДЗ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
public:
	
	DrivigCards();
	DrivigCards(int nmb_spd_ov, double mx_spd, int d,int m, int y);

	int GetNumbSpdOver() const;
	double GetMaxSpeed() const;
	void SetNumbSpdOver(int nmb_spd_ov);
	void Output() const;

}; 

///1.
/*
перегрузити конструктор DrivigCards з параметрами, щоб отримував const Date& замість int d,int m, int y
створюємо  клас Person, додаємо у  DrivigCards  поле - посилання на об'єкт Person.
Переписуємо конструктор DrivigCards  що приймає Person(іниціалізатори)
тестуємо в main

*/


//2.
/*

Дописати в Date поле char* monthstr;  "Jan", "Fab" динамічно виділяти пам'ять, не забуваємо вивільняти



*/


