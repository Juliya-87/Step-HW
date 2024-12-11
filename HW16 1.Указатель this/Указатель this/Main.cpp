#include <iostream>
#include "Student.h"

using namespace std;

int main()
{
	Student student("John", "Smith", 25);
	student.Show();

	Student st2(student);
	st2.Show();

	Student mas[2]{
		{ "John", "Smith", 25 },
		{ "Oleg", "Popov", 19 }
	};
	for (int i = 0; i < 2; i++)
	{
		mas[i].Show();
	}

	int count = Student::GetCount();
	cout << "Count: " << count << endl;

	return 0;
}


