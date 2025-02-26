#include "MyString.h"

using namespace std;

void MyString::AllocateChars(const size_t size)
{
	if (mChars == nullptr || mCapacity < size)
	{
		mCapacity = size;
		delete[] mChars;
		mChars = new char[mCapacity];
		mChars[0] = '\0';
	}
}

void MyString::Copy(const MyString& other)
{
	AllocateChars(other.mCapacity);
	strcpy_s(mChars, other.mCapacity, other.mChars);
}

void MyString::Move(MyString& other) noexcept
{
	char* chars = mChars;
	const size_t capacity = mCapacity;

	mChars = other.mChars;
	mCapacity = other.mCapacity;

	other.mCapacity = capacity;
	other.mChars = chars;
	other.mChars[0] = '\0';
}

MyString::MyString() : MyString(DEFAULT_SIZE)
{
}

MyString::MyString(const size_t size)
{
	AllocateChars(size);
}

MyString::MyString(const char* str)
{
	if (!str || !*str) {
		AllocateChars(1);
		return;
	}

	size_t strLength = strlen(str) + 1; // length including '\0'
	AllocateChars(strLength);
	memcpy(mChars, str, strLength);
}

MyString::MyString(const int value)
{
	AllocateChars(INT_BUFFER_SIZE);
	_itoa_s(value, mChars, mCapacity, 10);
}

MyString::MyString(const time_t value, const char* format)
{
	AllocateChars(TIME_BUFFER_SIZE);
	TimeToString(mChars, mCapacity, value, format);
}

MyString::MyString(const double value, const int precision)
{
	AllocateChars(DOUBLE_BUFFER_SIZE);
	DoubleToString(mChars, mCapacity, value, precision);
}

MyString::MyString(const MyString& other)
{
	Copy(other);
}

MyString::MyString(MyString&& other) noexcept
{
	Move(other);
}

size_t MyString::GetCapacity() const
{
	return mCapacity;
}

size_t MyString::GetLength() const
{
	return strlen(mChars);
}

const char* MyString::GetCStr() const
{
	return mChars;
}

void MyString::Assign(const char* str, const size_t maxLength)
{
	Clear();
	Append(str, maxLength);
}

void MyString::Append(const char* str, const size_t maxLength)
{
	if (!str || !*str || !maxLength)
	{
		return;
	}

	const size_t strLength = min(maxLength, strlen(str));
	const size_t oldLength = strlen(mChars);
	const size_t newLength = oldLength + strLength;

	if (mCapacity < newLength + 1) // +1 for '\0'
	{
		const size_t newCapacity = max(mCapacity * 2, newLength + 1);
		const auto newChars = new char[newCapacity];

		memcpy(newChars, mChars, oldLength + 1); // +1 to include '\0'

		delete[] mChars;
		mChars = newChars;
		mCapacity = newCapacity;
	}

	memcpy(mChars + oldLength, str, strLength);
	mChars[newLength] = '\0';
}

void MyString::Append(const char ch)
{
	Append(&ch, 1);
}

void MyString::Append(const int value)
{
	char buff[INT_BUFFER_SIZE];
	_itoa_s(value, buff, 10);

	Append(buff);
}

void MyString::Append(const MyString& str)
{
	Append(str.GetCStr());
}

void MyString::Append(const time_t value, const char* format)
{
	char buff[TIME_BUFFER_SIZE];
	TimeToString(buff, sizeof(buff), value, format);

	Append(buff);
}

void MyString::Append(const double value, const int precision)
{
	char buff[DOUBLE_BUFFER_SIZE];
	DoubleToString(buff, sizeof(buff), value, precision);

	Append(buff);
}

void MyString::Clear()
{
	mChars[0] = '\0';
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		Copy(other);
	}

	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		Move(other);
	}

	return *this;
}

bool MyString::operator==(const MyString& other) const
{
	return strcmp(mChars, other.mChars) == 0;
}

MyString::~MyString()
{
	delete[] mChars;
	mChars = nullptr;
}
