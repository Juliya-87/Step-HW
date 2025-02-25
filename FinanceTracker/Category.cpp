#include "Category.h"

#include <cstring>

Category::Category(const int id, const MyString& name) : ModelBase(id), mName(name)
{
}

const MyString& Category::GetName() const
{
	return mName;
}

void Category::Rename(const MyString& name)
{
	mName = name;
}

void Category::Parse(MyString& str)
{
	ModelBase::Parse(str);

	char* chars = str.GetCStr();
	char* context = nullptr;

	char* token = strtok_s(chars, DELIMITER, &context);
	mName = MyString(token);

	str = MyString(context);
}

MyString Category::ToString() const
{
	MyString str = ModelBase::ToString();
	str.Append(DELIMITER);
	str.Append(mName);
	return str;
}
