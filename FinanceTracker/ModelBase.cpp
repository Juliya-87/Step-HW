#include "ModelBase.h"

#include <cstdlib>
#include <cstring>

ModelBase::ModelBase(const int id)
{
	mId = id;
}

int ModelBase::GetId() const
{
	return mId;
}

void ModelBase::Parse(MyString& str)
{
	char* chars = str.GetCStr();
	char* context = nullptr;
	char* endPtr = nullptr;

	const char* token = strtok_s(chars, DELIMITER, &context);
	mId = strtol(token, &endPtr, 10);

	str = MyString(context);
}

MyString ModelBase::ToString() const
{
	return {mId};
}

bool ModelBase::operator==(const ModelBase& other) const
{
	return GetId() == other.GetId();
}
