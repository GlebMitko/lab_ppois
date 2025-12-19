#ifndef MINIMARKET_BANKING_REPORTGENERATOR_HPP
#define MINIMARKET_BANKING_REPORTGENERATOR_HPP

#include <string>
#include "Bank.hpp"
#include "RiskAssessor.hpp"

namespace minimarket {
namespace banking {

class ReportGenerator {
public:
    ReportGenerator(const std::string& format = "PDF");
    std::string generateFinancialReport(const Bank& bank) const;
    std::string generateRiskReport(const RiskAssessor& assessor) const;
    const std::string& getReportFormat() const { return reportFormat; }

private:
    std::string reportFormat;
};

} // namespace banking
} // namespace minimarket

#endif
