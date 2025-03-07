#pragma once
#include <ostream>
#include <vector>

class MyString final
{
public:
    MyString() = default;
    MyString(const char* str);
    MyString(const char* str, size_t length);
    MyString(size_t number, char ch);
    MyString(const MyString& str) = default;
    MyString(MyString&& str) noexcept;

    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;
    MyString operator+(const MyString& other) const;
    MyString operator+(const char* str) const;
    bool operator==(const MyString& other) const;
    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);

    size_t GetLength() const;
    const char* GetCStr() const;

    bool IsEmpty() const;
    bool Contains(char ch) const;
    size_t Find(char ch, size_t startPosition = 0) const;
    void Assign(const char* str);
    void Assign(const char* str, size_t length);
    void Append(const char* str);
    void Append(const char* str, size_t length);
    void Append(size_t number, char ch);
    void Append(const MyString& str);
    void Insert(size_t position, const char* str);
    void Clear();

private:
    std::vector<char> mChars = { '\0' };
};

template <>
struct std::hash<MyString> {
	size_t operator()(const MyString& str) const noexcept
	{
		size_t hashValue = 0;
		const char* chars = str.GetCStr();
		for (size_t i = 0; i < str.GetLength(); ++i) {
			hashValue = hashValue * 31 + std::hash<char>()(chars[i]);
		}
		return hashValue;
	}
};
