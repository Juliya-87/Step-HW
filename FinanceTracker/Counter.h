#pragma once
#include "Serializable.h"
class Counter final : public Serializable
{
private:
	MyString mName;
	int mValue = 0;

public:
	Counter() = default;
	Counter(const MyString& name);

	int GetNextValue();
	const MyString& GetName() const;

	std::unordered_map<MyString, MyString> ToMap() const override;
	void FromMap(const std::unordered_map<MyString, MyString>& data) override;

	bool operator==(const Counter& other) const;
};
