#pragma once


#include "DrivіngCards.h"


/*

При створені обьекта класу спочатку створюється обьект(в пам_яті виділяється місце під
цей обьект, потім вже спрацьовує конструктор.

 Якщо полями класу виступають:

- константи
- посилання
-поле об'єкт іншого класу ,без конструктора за замовчуванням

тоді ці поля мають бути проініціалізовані на момент створення,
тобто ще до того як спрацює  конструктор, який ініціалізує вже існуючі поля класу
Тому існують ініціалізатори

Ім_я конструктора (): ім_я поля(значення)

Ініціалізатори спрацьовують в момент створення обьекту, до роботи конструктора

*/


DrivigCards::DrivigCards() : max_speed(50), dat(0,0,0)//////ініціалізатор для константного поля max_speed   no Date()
/////якщо таких ініціалізаторів декілька, отримуємо
//// список ініціалізаціі   
{
	
	numb_speed_over = 0;
}



DrivigCards::DrivigCards(int nmb_spd_ov, double mx_spd, int d, int m, int y) :max_speed(mx_spd), dat(d,m,y)///// в ініціалізаторі визивається конструктор з параметрами для поля dat
{
	numb_speed_over = nmb_spd_ov;


	/////Спочатку створити об'єкт а потім визвати сеттери не вийде,нема конструктора за замовч у поля Date dat; 
	/*dat.SetDay(d);
	dat.SetMonth(m);
	dat.SetYear(y);*/

}

DrivigCards::DrivigCards(int nmb_spd_ov, double mx_spd, int d, int m, int y, Person& prs):max_speed(mx_spd), dat(d, m, y),  для посилання
{




}

int DrivigCards::GetNumbSpdOver() const
{
	return numb_speed_over;
}

double DrivigCards::GetMaxSpeed() const
{
	return max_speed;
}

void DrivigCards::SetNumbSpdOver(int nmb_spd_ov)
{
	numb_speed_over = nmb_spd_ov;
}

void DrivigCards::Output() const
{
	cout << "Over speed: " << numb_speed_over << endl;
	cout << "Max speed: " << max_speed << endl;
	
	//cout << "Day: " << dat.GetDay() << endl;


	dat.Output();
}
