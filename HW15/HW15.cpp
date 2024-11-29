#include <iostream>

using namespace std;


// Задание
// Реализуйте класс Дробь.Необходимо хранить числитель и знаменатель в качестве переменных - членов.
// Реализуйте функции - члены для ввода данных в переменные - члены, для выполнения арифметических операций
// (сложение, вычитание, умножение, деление, и т.д.)


class Fraction
{
private:
	int mNumerator = 0;
	int mDenominator = 1;

public:
	bool try_set(int numerator, int denominator)
	{
		if (denominator == 0)
		{
			return false;
		}

		mNumerator = numerator;
		mDenominator = denominator;
		return true;
	}

	void print_line()
	{
		cout << "Numerator: " << mNumerator <<'\n';
		cout << "Denominator: " << mDenominator << '\n';
		cout << '\n';
	}

	void sum(int num)
	{
		mNumerator += num * mDenominator;
	}

	void subtract(int num)
	{
		mNumerator -= num * mDenominator;
	}

	void multiply(int num)
	{
		mNumerator *= num;
	}

	void divide(int num)
	{
		mDenominator *= num;
	}
};

int main()
{
	int n = 2;
	int d = 5;
	int num = 3;

	Fraction fraction;
	fraction.try_set(n, d);
	fraction.print_line();

	fraction.sum(num);
	cout << "Sum:" << '\n';
	fraction.print_line();

	fraction.subtract(num);
	cout << "Subtract:" << '\n';
	fraction.print_line();

	fraction.multiply(num);
	cout << "Multiply:" << '\n';
	fraction.print_line();

	fraction.divide(num);
	cout << "Devide:" << '\n';
	fraction.print_line();
}