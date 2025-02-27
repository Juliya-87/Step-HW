#include "MyString.h"

#include <stdexcept>

using namespace std;

MyString::MyString(const char* str)
{
	Append(str);
}

MyString::MyString(const char* str, const size_t length)
{
	Append(str, length);
}

MyString::MyString(const size_t number, const char ch)
{
	Append(number, ch);
}

MyString::MyString(MyString&& str) noexcept : mChars(std::move(str.mChars))
{
	str.mChars.assign(1, '\0');
}

size_t MyString::GetLength() const
{
	return mChars.size() - 1; // last one is '\0'
}

const char* MyString::GetCStr() const
{
	return mChars.data();
}

void MyString::Assign(const char* str)
{
	Assign(str, strlen(str));
}

void MyString::Assign(const char* str, const size_t length)
{
	Clear();
	Append(str, length);
}

void MyString::Append(const char* str)
{
	Append(str, strlen(str));
}

void MyString::Append(const char* str, const size_t length)
{
	if (!str || !length)
	{
		return;
	}

	mChars.insert(mChars.end() - 1, str, str + length);
}

void MyString::Append(const size_t number, const char ch)
{
	if (!number)
	{
		return;
	}

	mChars.insert(mChars.end() - 1, number, ch);
}

void MyString::Append(const MyString& str)
{
	Append(str.GetCStr());
}

void MyString::Insert(const size_t position, const char* str)
{
	if (!str || !*str)
	{
		return;
	}

	if (position > GetLength())
	{
		throw std::out_of_range("Position is out of bounds");
	}

	const size_t strLength = strlen(str);
	mChars.insert(mChars.begin() + position, str, str + strLength);
}

void MyString::Clear()
{
	mChars.assign(1, '\0');
}

bool MyString::Contains(const char ch) const
{
	return ranges::find(mChars, ch) != mChars.end();
}

size_t MyString::Find(const char ch, const size_t startPosition) const
{
	if (startPosition > GetLength())
	{
		return SIZE_MAX;
	}

	const auto result = ranges::find(mChars.begin() + startPosition, mChars.end(), ch);
	return result == mChars.end() ? SIZE_MAX : result - mChars.begin();
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		mChars = other.mChars;
	}

	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		mChars = std::move(other.mChars);
		other.mChars.assign(1, '\0');
	}

	return *this;
}

bool MyString::operator==(const MyString& other) const
{
	return mChars == other.mChars;
}

bool MyString::operator<(const MyString& other) const
{
	return mChars < other.mChars;
}

ostream& operator<<(ostream& os, const MyString& str)
{
	os << str.GetCStr();
	return os;
}

char& MyString::operator[](const size_t pos)
{
	return mChars[pos];
}

const char& MyString::operator[](const size_t pos) const
{
	return mChars[pos];
}
