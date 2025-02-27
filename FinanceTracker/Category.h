#pragma once
#include "ModelBase.h"

class Category final : public ModelBase
{
private:
	MyString mName;

public:
	Category() = default;
	Category(int id, const MyString& name);

	const MyString& GetName() const;

	void Rename(const MyString& name);

	std::map<MyString, MyString> ToMap() const override;
	void FromMap(const std::map<MyString, MyString>& data) override;
};