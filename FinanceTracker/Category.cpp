#include "Category.h"

using namespace std;

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

map<MyString, MyString> Category::ToMap() const
{
	map<MyString, MyString> map = ModelBase::ToMap();

	map.emplace("Name", mName);

	return map;
}

void Category::FromMap(const map<MyString, MyString>& data)
{
	ModelBase::FromMap(data);

	mName = data.at("Name");
}
