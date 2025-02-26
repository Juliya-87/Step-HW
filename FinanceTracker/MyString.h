#pragma once
#include <ctime>

#include "ConversionHelpers.h"

class MyString final
{
private:
    static constexpr size_t DEFAULT_SIZE = 15;
    static constexpr size_t REALLOCATION_STEP = 15;
	static constexpr int DEFAULT_PRECISION = 2;
	static constexpr size_t DOUBLE_BUFFER_SIZE = 20;
    static constexpr size_t TIME_BUFFER_SIZE = 25;
    static constexpr size_t INT_BUFFER_SIZE = 12;

    char* mChars = nullptr;
    size_t mCapacity = 0;

    void AllocateChars(size_t size);

    void Copy(const MyString& other);

    void Move(MyString& other) noexcept;

public:
    MyString();
    MyString(size_t size);
    MyString(const char* str);
	MyString(int value);
    MyString(time_t value, const char* format = DEFAULT_TIME_FORMAT);
	MyString(double value, int precision = DEFAULT_PRECISION);
    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;

	size_t GetCapacity() const;
    size_t GetLength() const;
    const char* GetCStr() const;

    void Assign(const char* str, size_t maxLength = SIZE_MAX);

    void Append(const char* str, size_t maxLength = SIZE_MAX);
    void Append(char ch);
    void Append(int value);
    void Append(const MyString& str);
    void Append(time_t value, const char* format = DEFAULT_TIME_FORMAT);
    void Append(double value, int precision = DEFAULT_PRECISION);

    void Clear();

    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;
    bool operator==(const MyString& other) const;

    ~MyString();
};
