#pragma once
#include <ctime>

#include "MyString.h"
#include "ReportData.h"
#include "ReportingPeriod.h"
#include "SpendingTransactionRepository.h"

class Report
{
public:
	virtual ~Report() = default;

	void Print(ReportingPeriod period) const;
	void Export(ReportingPeriod period) const;

protected:
	Report(const MyString& reportName, const std::shared_ptr<SpendingTransactionRepository>& spendingTransactionRepository, const std::shared_ptr<FileHandler>& fileHandler, const std::shared_ptr<Settings>& settings);

	virtual std::unique_ptr<ReportData> GetReportData(ReportingPeriod period) const = 0;

	static time_t GetStartTime(ReportingPeriod period);

	MyString mReportName;
	std::shared_ptr<SpendingTransactionRepository> mSpendingTransactionRepository;

private:
	MyString GetFullFileName() const;

	std::shared_ptr<FileHandler> mFileHandler;
	std::shared_ptr<Settings> mSettings;

	static constexpr char TIME_FORMAT[] = "%Y-%m-%d %H%M%S";
};
