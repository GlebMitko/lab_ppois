#include "../../include/banking/InvestmentAccount.hpp"

namespace minimarket {
namespace banking {

InvestmentAccount::InvestmentAccount(const std::string& number, const std::string& name,
                                     const std::string& type, double risk)
    : Account(number, name), investmentType(type), riskLevel(risk) {}

double InvestmentAccount::calculateExpectedReturn() const {
    return calculateInterest() * (1.0 + riskLevel / 10.0);
}

bool InvestmentAccount::rebalancePortfolio() {
    return riskLevel > 0.5;
}

} // namespace banking
} // namespace minimarket
