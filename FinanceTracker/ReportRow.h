#pragma once
#include <vector>

#include "ReportCell.h"

class ReportRow final
{
private:
	std::vector<std::unique_ptr<ReportCell>> mCells;

public:
	const std::vector<std::unique_ptr<ReportCell>>& GetCells() const;

	void AddCell(const MyString& value, std::streamsize width = 0, bool isLeftAligned = true);
};

