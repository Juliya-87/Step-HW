
/////DZ   перегрузить конструктор копирования чтобы срабатыва счетчик количесва точек static int count!!!!!!!!!!!!!!!!!!!

#include<iostream>
using namespace std;

class Point
{
private:
	int x;/////поля індивідуальні для кожного обьекту
	int y;
	int z;
	static int count;////статичне поле, котре є спільним для всіх екземплярів класу, належить класу

	// Экземплярные поля принадлежат конкретным обьектам
	// Статические поля : общие для всех обьектов

public:

	Point()
	{
		cout << "Construct ()  \n";
		x = y = z = 0;
		count++;
	}

	~Point()
	{
		count--;
	}

	Point(const int x1)
	{
		x = x1;
		y = x;
		z = 0;
		count++;
	}

	Point(const int x1, const int y1) :Point(x1)
	{
		y = y1;
	}

	Point(const int x1, const int y1, const int z1) : Point(x1, y1)
	{
		z = z1;
	}

	Point(const Point& pnt) : Point(pnt.x, pnt.y, pnt.z)
	{
	}


	void Output() const
	{
		cout << "X: " << x << "\tY: " << y << "\tZ: " << z << endl;
		cout << "Count: " << count << endl;
	}

	//////  методы аксессоры

	int GetX() const  // инспекторы
	{
		return x;
	}

	int GetY() const
	{
		return y;
	}

	/////  Модификаторы 
	void SetX(const int X)
	{
		// X <100
		if (X > 100)
		{
			cout << "Error\n";
			x = 0;
		}
		else
		{
			x = X;
		}
	}
	void SetY(int y)
	{
		y = y;////тут ми звертаэмось лише до параметру

		this->y = y;
	}

	static int GetCount()
	{
		///cout << x;   так як не отримує неявно  this статичні методи не можуть звертатися до екземплярних методів і полів
		/////x = 5;
		///Output();
		return count;
	}
};


int Point::count = 0;//// ініціалізація статичного поля

/*
Синтаксис делегирования:
Имя_класса ( параметры (формальные) ) : имя_класса ( формальная передача параметров )
{
тело;
};

*/

void Show(Point obj)///передача  копіі
{
	obj.Output();
}


Point CreateObj()
{
	Point obj;
	return obj;
}/////по завершенні роботи вункціі obj зруйнується, а його копія повернеться в coller

void main()
{
	Point obj1;/////   конструктор по умолчанию ()
	obj1.Output();
	///////Контструктор копіювання

	///1. Ініціалізація одного обьекта іншим
	Point obj2(obj1);   ////Point( const Point& pnt) спрацює конструктор копі.вання що існу за замовчуванням
	////////Конструкторок копіювання за замовчуванням робить побітову копію обьекту

	//Конструктор копирования есть по умолчанию:  копирует побитово
	// Конструктор копирования перепределенный выделяет отдельную обл памяти, а не копирует указатели

	obj2.Output();

	///2. Коли передаємо обьєкт у функцію за значенням(за копією)

	//Show(obj1);//////створиться локальна змінна Point obj(obj1), і також спрацює конструктор копі

	////3. Повернення копіі обьєкту з функціі

	//obj1 = CreateObj();
}