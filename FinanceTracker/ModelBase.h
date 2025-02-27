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

	std::map<MyString, MyString> ToMap() const override;
	void FromMap(const std::map<MyString, MyString>& data) override;

	bool operator==(const ModelBase& other) const;
};

