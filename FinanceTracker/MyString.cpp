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
	delete[] mChars;

	mChars = other.mChars;
	mCapacity = other.mCapacity;

	other.mCapacity = DEFAULT_SIZE;
	other.mChars = new char[other.mCapacity];
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
	AllocateChars(strlen(str) + 1);
	strcpy_s(mChars, mCapacity, str);
}

MyString::MyString(const int value)
{
	AllocateChars(INT_BUFFER_SIZE);
	_itoa_s(value, mChars, mCapacity, 10);
}

MyString::MyString(const time_t value, const char* format)
{
	AllocateChars(TIME_BUFFER_SIZE);
	TimeToString(mChars, static_cast<int>(mCapacity), value, format);
}

MyString::MyString(const double value, const int precision)
{
	AllocateChars(DOUBLE_BUFFER_SIZE);
	DoubleToString(mChars, static_cast<int>(mCapacity), value, precision);
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

char* MyString::GetCStr() const
{
	return mChars;
}

void MyString::Append(const char* str)
{
	const size_t newLength = strlen(mChars) + strlen(str) + 1;

	if (mCapacity < newLength)
	{
		mCapacity *= 2;
		if (mCapacity < newLength)
		{
			mCapacity = newLength;
		}

		const auto newChars = new char[mCapacity];
		strcpy_s(newChars, mCapacity, mChars);
		delete[] mChars;
		mChars = newChars;
	}

	strcat_s(mChars, mCapacity, str);
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
