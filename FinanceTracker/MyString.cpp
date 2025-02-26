#include "MyString.h"

using namespace std;

void MyString::AllocateChars(const size_t size)
{
	if (mChars == nullptr || mCapacity < size)
	{
		mChars = make_unique<char[]>(size);
		mCapacity = size;
		mChars[0] = '\0';
	}
}

void MyString::Copy(const MyString& other)
{
	AllocateChars(other.mCapacity);
	strcpy_s(mChars.get(), other.mCapacity, other.mChars.get());
}

void MyString::Move(MyString& other) noexcept
{
	mChars = std::move(other.mChars);
	mCapacity = other.mCapacity;

	other.AllocateChars(DEFAULT_SIZE);
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
	memcpy(mChars.get(), str, strLength);
}

MyString::MyString(const int value)
{
	AllocateChars(INT_BUFFER_SIZE);
	_itoa_s(value, mChars.get(), mCapacity, 10);
}

MyString::MyString(const time_t value, const char* format)
{
	AllocateChars(TIME_BUFFER_SIZE);
	TimeToString(mChars.get(), mCapacity, value, format);
}

MyString::MyString(const double value, const int precision)
{
	AllocateChars(DOUBLE_BUFFER_SIZE);
	DoubleToString(mChars.get(), mCapacity, value, precision);
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
	return strlen(mChars.get());
}

const char* MyString::GetCStr() const
{
	return mChars.get();
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
	const size_t oldLength = strlen(mChars.get());
	const size_t newLength = oldLength + strLength;

	if (mCapacity < newLength + 1) // +1 for '\0'
	{
		const size_t newCapacity = max(mCapacity + REALLOCATION_STEP, newLength + 1);
		auto newChars = make_unique<char[]>(newCapacity);

		memcpy(newChars.get(), mChars.get(), oldLength + 1); // +1 to include '\0'

		mChars = std::move(newChars);
		mCapacity = newCapacity;
	}

	memcpy(mChars.get() + oldLength, str, strLength);
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
	return strcmp(mChars.get(), other.mChars.get()) == 0;
}
