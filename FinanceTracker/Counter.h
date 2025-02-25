#pragma once
#include "Serializable.h"
class Counter final : public Serializable
{
private:
	MyString mName;
	int mValue = 0;

protected:
	void Parse(MyString& str) override;
	MyString ToString() const override;

public:
	Counter() = default;
	Counter(const MyString& name);

	int GetNextValue();
	const MyString& GetName() const;

	bool operator==(const Counter& other) const;
};

