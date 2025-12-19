#include "../../include/banking/TaxCalculator.hpp"
#include <algorithm>

namespace minimarket {
namespace banking {

TaxCalculator::TaxCalculator(double rate) : taxRate(rate) {}

double TaxCalculator::calculateTax(double income) const {
    return income * taxRate / 100;
}

double TaxCalculator::calculateDeductions(double income) const {
    return std::min(income * 0.1, 5000.0);
}

} // namespace banking
} // namespace minimarket
