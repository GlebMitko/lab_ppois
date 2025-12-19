#include "../../include/banking/RiskAssessor.hpp"

namespace minimarket {
namespace banking {

RiskAssessor::RiskAssessor(double threshold) : riskThreshold(threshold) {}

double RiskAssessor::assessInvestmentRisk(double volatility, double returnRate) const {
    if (returnRate == 0) return volatility > 0 ? 1e9 : 0;
    return volatility / returnRate;
}

bool RiskAssessor::approveLoan(const CreditScore& score, double amount) const {
    return score.qualifyForLoan(amount) && amount <= riskThreshold;
}

} // namespace banking
} // namespace minimarket
