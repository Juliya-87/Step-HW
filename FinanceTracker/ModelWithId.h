#pragma once
#include "Model.h"

class ModelWithId : public Model<int>
{
public:
	int GetId() const;
	int GetKey() const override;

	std::unordered_map<MyString, MyString> ToMap() const override;
	void FromMap(const std::unordered_map<MyString, MyString>& data) override;

protected:
	ModelWithId() = default;
	ModelWithId(int id);

private:
	int mId = 0;
};
