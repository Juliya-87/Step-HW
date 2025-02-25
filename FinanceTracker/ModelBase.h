#pragma once
#include "Serializable.h"

class ModelBase : public Serializable
{
private:
	int mId = 0;

protected:
	ModelBase() = default;
	ModelBase(int id);

public:
	int GetId() const;

	void Parse(MyString& str) override;
	MyString ToString() const override;

	bool operator==(const ModelBase& other) const;
};

