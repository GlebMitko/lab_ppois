#include "../../include/banking/ReportGenerator.hpp"

namespace minimarket {
namespace banking {

ReportGenerator::ReportGenerator(const std::string& format) : reportFormat(format) {}

std::string ReportGenerator::generateFinancialReport(const Bank& bank) const {
    return "Financial Report: Total Assets = " + std::to_string(bank.calculateTotalAssets());
}

std::string ReportGenerator::generateRiskReport(const RiskAssessor& assessor) const {
    return "Risk Report: Threshold = " + std::to_string(assessor.getRiskThreshold());
}

} // namespace banking
} // namespace minimarket
