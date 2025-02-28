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

unordered_map<MyString, MyString> Category::ToMap() const
{
	auto map = ModelBase::ToMap();

	map.emplace("Name", mName);

	return map;
}

void Category::FromMap(const unordered_map<MyString, MyString>& data)
{
	ModelBase::FromMap(data);

	mName = data.at("Name");
}
