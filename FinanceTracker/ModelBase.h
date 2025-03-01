#pragma once
#include "Serializable.h"

class ModelBase : public Serializable
{
public:
	bool operator==(const ModelBase& other) const;

	int GetId() const;

	std::unordered_map<MyString, MyString> ToMap() const override;
	void FromMap(const std::unordered_map<MyString, MyString>& data) override;

protected:
	ModelBase() = default;
	ModelBase(int id);

private:
	int mId = 0;
};
