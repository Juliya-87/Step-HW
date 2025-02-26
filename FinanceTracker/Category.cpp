#include "Category.h"

#include "StringTokenExtractor.h"

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

	StringTokenExtractor splitter(str, DELIMITER);
	MyString token;

	splitter.GetNextToken(token);
	mName = std::move(token);

	str = splitter.GetRemaining();
}

MyString Category::ToString() const
{
	MyString str = ModelBase::ToString();
	str.Append(DELIMITER);
	str.Append(mName);
	return str;
}
