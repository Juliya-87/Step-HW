#include "ModelBase.h"

#include "ConversionHelpers.h"

bool ModelBase::operator==(const ModelBase& other) const
{
	return GetId() == other.GetId();
}

int ModelBase::GetId() const
{
	return mId;
}

std::unordered_map<MyString, MyString> ModelBase::ToMap() const
{
	return { {"Id", ToString(mId)} };
}

void ModelBase::FromMap(const std::unordered_map<MyString, MyString>& data)
{
	mId = StrToInt(data.at("Id"));
}

ModelBase::ModelBase(const int id)
{
	mId = id;
}
