#pragma once
#include <ostream>
#include <vector>

class MyString final
{
private:
	std::vector<char> mChars = { '\0' };

public:
    MyString() = default;
    MyString(const char* str);
    MyString(const char* str, size_t length);
    MyString(size_t number, char ch);
    MyString(const MyString& str) = default;
    MyString(MyString&& str) noexcept;

    size_t GetLength() const;
    const char* GetCStr() const;

    void Assign(const char* str);
    void Assign(const char* str, size_t length);

    void Append(const char* str);
    void Append(const char* str, size_t length);
    void Append(size_t number, char ch);
    void Append(const MyString& str);

    void Insert(size_t position, const char* str);

    void Clear();

    bool Contains(char ch) const;
    size_t Find(char ch, size_t startPosition = 0) const;

	MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;
    bool operator==(const MyString& other) const;
	bool operator<(const MyString& other) const;
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;
};
