#pragma once
#include "ModelWithId.h"

class Category final : public ModelWithId
{
public:
	Category() = default;
	Category(int id, const MyString& name);

	const MyString& GetName() const;

	void Rename(const MyString& name);

	std::unordered_map<MyString, MyString> ToMap() const override;
	void FromMap(const std::unordered_map<MyString, MyString>& data) override;

private:
	MyString mName;
};