#include "../../include/banking/Loan.hpp"

namespace minimarket {
namespace banking {

Loan::Loan(double principal, double rate, int term)
    : principalAmount(principal), interestRate(rate), termMonths(term) {}

double Loan::calculateMonthlyPayment() const {
    if (termMonths <= 0 || interestRate < 0) return 0.0;
    double monthlyRate = interestRate / 100 / 12;
    return principalAmount * monthlyRate * std::pow(1 + monthlyRate, termMonths) /
           (std::pow(1 + monthlyRate, termMonths) - 1);
}

double Loan::calculateTotalInterest() const {
    return calculateMonthlyPayment() * termMonths - principalAmount;
}

} // namespace banking
} // namespace minimarket
