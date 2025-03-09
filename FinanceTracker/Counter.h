#pragma once
#include "Model.h"

class Counter final : public Model<MyString>
{
public:
	Counter() = default;
	Counter(const MyString& name);

	int GetNextValue();
	const MyString& GetName() const;
	MyString GetKey() const override;

	std::unordered_map<MyString, MyString> ToMap() const override;
	void FromMap(const std::unordered_map<MyString, MyString>& data) override;

private:
	MyString mName;
	int mValue = 0;
};
