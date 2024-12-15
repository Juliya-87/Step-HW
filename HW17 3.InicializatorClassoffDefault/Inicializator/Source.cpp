#include <iostream>

#include "DrivіngCards.h"



using namespace std;


int a_g;////global variable


void f()
{
	//Date d1;/// Date()
} //// ~Date()


int main()
{
	
	//cout << a_g << endl;////ok

	//int a;
	//cout << a << endl;////error

	//f();

	//Date* d1 = new Date();/// Date()
	//delete d1;  //// ~Date()

	/////1.Об'явлення об'єктів що потребують ОБОВ'ЯЗКОВОЇ ініціалізації

	//1.1. константи


	
	const double pi = 3.14;

	//const double& ref = pi;


	//1.2. посилання, ініціалізуються на момент створення !!!!, не перенаправляються
	int age = 10;
	int& refa=age ;
	


	///вказівники можемо перенаправляти
	int* ptr;
	ptr = nullptr;
	//if (ptr != nullptr)
	//	delete ptr;


	//////2.


	//DrivigCards obj;
	//obj.Output();



	//Date dat(13, 10,2023);

	/*DrivigCards obj1(70, 30, 9, 10, 2023);
	obj1.Output();*/


	//Person pers;


	///3,  Створення об'єкту без конструктора за замовчуванням

	//Date dat;////є очікування конструктора за замовчуванням , а його нема
	{
		Date dat(13, 10, 2023);

	}/////  ~Date()


//	Date& ref = dat;

	//Date obj;


	Date dat(13, 10, 2023);

	Date dat1(13, 10, 2023);

	Date dat2(dat);  //// copy

	//dat.TestConst(dat1);///// константний  вказівник  на константу    this* --  він дивиться на dat як на константу

	//dat.Output();//////  Екземплярний метод Output(не статичний)   один в пам'яті для всіх   об'єктів дат.   Об'єкт dat потрапляє в  Output чере звказівник this
	//dat1.Output();///  Об'єкт dat1 потрапляє в  Output чере звказівник this



	//




}