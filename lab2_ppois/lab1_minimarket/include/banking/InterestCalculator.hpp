#ifndef MINIMARKET_BANKING_INTERESTCALCULATOR_HPP
#define MINIMARKET_BANKING_INTERESTCALCULATOR_HPP

namespace minimarket {
namespace banking {

class InterestCalculator {
public:
    InterestCalculator(double rate);
    double calculateCompoundInterest(double principal, int years) const;
    double calculateSimpleInterest(double principal, int years) const;
    double getBaseRate() const { return baseRate; }

private:
    double baseRate;
};

} // namespace banking
} // namespace minimarket

#endif
