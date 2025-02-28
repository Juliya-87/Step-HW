#pragma once
#include <vector>

#include "ReportRow.h"

class ReportData final
{
private:
	std::vector<std::unique_ptr<ReportRow>> mRows;

public:
	const std::vector<std::unique_ptr<ReportRow>>& GetRows() const;

	ReportRow* CreateRow();
};
