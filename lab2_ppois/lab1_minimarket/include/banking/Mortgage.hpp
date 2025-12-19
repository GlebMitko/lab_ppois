#ifndef MINIMARKET_BANKING_MORTGAGE_HPP
#define MINIMARKET_BANKING_MORTGAGE_HPP

#include "Loan.hpp"
#include <string>

namespace minimarket {
namespace banking {

class Mortgage : public Loan {
public:
    Mortgage(double principal, double rate, int term, const std::string& address, double down);
    bool validateDownPayment() const;
    double calculateLTV() const;
    const std::string& getPropertyAddress() const { return propertyAddress; }
    double getDownPayment() const { return downPayment; }

private:
    std::string propertyAddress;
    double downPayment;
};

} // namespace banking
} // namespace minimarket

#endif
