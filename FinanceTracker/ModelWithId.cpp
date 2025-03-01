#include "ModelWithId.h"

#include "ConversionHelpers.h"

bool ModelWithId::operator==(const ModelWithId& other) const
{
	return GetId() == other.GetId();
}

int ModelWithId::GetId() const
{
	return mId;
}

std::unordered_map<MyString, MyString> ModelWithId::ToMap() const
{
	return { {"Id", ToString(mId)} };
}

void ModelWithId::FromMap(const std::unordered_map<MyString, MyString>& data)
{
	mId = StrToInt(data.at("Id"));
}

ModelWithId::ModelWithId(const int id)
{
	mId = id;
}
