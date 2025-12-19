#ifndef MINIMARKET_BANKING_RISKASSESSOR_HPP
#define MINIMARKET_BANKING_RISKASSESSOR_HPP

#include "CreditScore.hpp"

namespace minimarket {
namespace banking {

class RiskAssessor {
public:
    RiskAssessor(double threshold = 100000.0);
    double assessInvestmentRisk(double volatility, double returnRate) const;
    bool approveLoan(const CreditScore& score, double amount) const;
    double getRiskThreshold() const { return riskThreshold; }

private:
    double riskThreshold;
};

} // namespace banking
} // namespace minimarket

#endif
