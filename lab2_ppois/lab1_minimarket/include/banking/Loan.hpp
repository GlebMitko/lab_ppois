#ifndef MINIMARKET_BANKING_LOAN_HPP
#define MINIMARKET_BANKING_LOAN_HPP

#include <cmath>

namespace minimarket {
namespace banking {

class Loan {
public:
    Loan(double principal, double rate, int term);
    double calculateMonthlyPayment() const;
    double calculateTotalInterest() const;
    double getPrincipalAmount() const { return principalAmount; }
    double getInterestRate() const { return interestRate; }
    int getTermMonths() const { return termMonths; }

protected:
    double principalAmount;
    double interestRate;
    int termMonths;
};

} // namespace banking
} // namespace minimarket

#endif
