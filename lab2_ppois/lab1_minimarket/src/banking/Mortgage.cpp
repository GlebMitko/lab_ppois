#include "../../include/banking/Mortgage.hpp"

namespace minimarket {
namespace banking {

Mortgage::Mortgage(double principal, double rate, int term,
                   const std::string& address, double down)
    : Loan(principal, rate, term), propertyAddress(address), downPayment(down) {}

bool Mortgage::validateDownPayment() const {
    return downPayment >= getPrincipalAmount() * 0.2;
}

double Mortgage::calculateLTV() const {
    return (getPrincipalAmount() - downPayment) / getPrincipalAmount() * 100;
}

} // namespace banking
} // namespace minimarket
