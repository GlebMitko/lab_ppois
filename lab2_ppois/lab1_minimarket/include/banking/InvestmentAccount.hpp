#ifndef MINIMARKET_BANKING_INVESTMENTACCOUNT_HPP
#define MINIMARKET_BANKING_INVESTMENTACCOUNT_HPP

#include "Account.hpp"
#include <string>

namespace minimarket {
namespace banking {

class InvestmentAccount : public Account {
public:
    InvestmentAccount(const std::string& number, const std::string& name,
                      const std::string& type, double risk);
    double calculateExpectedReturn() const;
    bool rebalancePortfolio();

    const std::string& getInvestmentType() const { return investmentType; }
    double getRiskLevel() const { return riskLevel; }

private:
    std::string investmentType;
    double riskLevel;
};

} // namespace banking
} // namespace minimarket

#endif
