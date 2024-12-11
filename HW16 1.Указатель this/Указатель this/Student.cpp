#include "Student.h"
#include <functional>
#include <iostream>

using namespace std;

int Student::count = 0;

Student::~Student()
{
	cout << "Destruct\n";
	if (name != nullptr)
	{
		delete[]name;
		name = nullptr;
	}
	if (surname != nullptr)
	{
		delete[]surname;
		surname = nullptr;
	}

}
Student::Student()
{
	age = 0;
	name = nullptr;
	surname = nullptr;
	count++;

}
Student::Student(const char* name, const char* surname, unsigned int age)
{
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);

	this->surname = new char[strlen(surname) + 1];
	strcpy_s(this->surname, strlen(surname) + 1, surname);
	this->age = age;

	count++;
}

Student::Student(const Student& st) : Student(st.name, st.surname, st.age)
{
}

void Student::Show() const
{
	// Здесь this является необязательным, однако использовать его можно.
	cout << "Name: " << name << endl;
	cout << "Surname: " << this->surname << endl;
	cout << "Age: " << this->age << endl;
}