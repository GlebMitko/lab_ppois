#include "../../include/banking/InterestCalculator.hpp"
#include <cmath>

namespace minimarket {
namespace banking {

InterestCalculator::InterestCalculator(double rate) : baseRate(rate) {}

double InterestCalculator::calculateCompoundInterest(double principal, int years) const {
    return principal * std::pow(1 + baseRate/100, years) - principal;
}

double InterestCalculator::calculateSimpleInterest(double principal, int years) const {
    return principal * baseRate / 100 * years;
}

} // namespace banking
} // namespace minimarket
