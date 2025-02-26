#include "ModelBase.h"

#include <cstdlib>

#include "StringTokenExtractor.h"

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
	StringTokenExtractor splitter(str, DELIMITER);
	MyString token;
	char* endPtr = nullptr;

	splitter.GetNextToken(token);
	mId = strtol(token.GetCStr(), &endPtr, 10);

	str = splitter.GetRemaining();
}

MyString ModelBase::ToString() const
{
	return {mId};
}

bool ModelBase::operator==(const ModelBase& other) const
{
	return GetId() == other.GetId();
}
