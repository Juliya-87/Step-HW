#pragma once

// Класс студент.
class Student
{
private:

    static int count;
	// Возраст.
    unsigned int age;
    // Имя.
    char * name;
    // Фамилия.
    char * surname;
 
public:

    Student();
	Student(const char * name, const char * surname, unsigned int age);

    ///copy constructor  DZ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ///
    Student(const Student& st);

    ///Добавить статическое поле count и статический метод геттер

    void Show() const;

    void SetAge(int value) { this->age = value; }

    static int GetCount()
    {
        return count;
    }

	~Student();
};

