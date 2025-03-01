#pragma once
#include "Serializable.h"
class Counter final : public Serializable
{
public:
	Counter() = default;
	Counter(const MyString& name);

	bool operator==(const Counter& other) const;

	int GetNextValue();
	const MyString& GetName() const;

	std::unordered_map<MyString, MyString> ToMap() const override;
	void FromMap(const std::unordered_map<MyString, MyString>& data) override;

private:
	MyString mName;
	int mValue = 0;
};
