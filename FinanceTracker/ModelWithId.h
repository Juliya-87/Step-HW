#pragma once
#include "Serializable.h"

class ModelWithId : public Serializable
{
public:
	bool operator==(const ModelWithId& other) const;

	int GetId() const;

	std::unordered_map<MyString, MyString> ToMap() const override;
	void FromMap(const std::unordered_map<MyString, MyString>& data) override;

protected:
	ModelWithId() = default;
	ModelWithId(int id);

private:
	int mId = 0;
};
