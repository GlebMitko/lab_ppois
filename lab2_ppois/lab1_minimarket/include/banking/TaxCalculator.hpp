#ifndef MINIMARKET_BANKING_TAXCALCULATOR_HPP
#define MINIMARKET_BANKING_TAXCALCULATOR_HPP

namespace minimarket {
namespace banking {

class TaxCalculator {
public:
    TaxCalculator(double rate);
    double calculateTax(double income) const;
    double calculateDeductions(double income) const;
    double getTaxRate() const { return taxRate; }

private:
    double taxRate;
};

} // namespace banking
} // namespace minimarket

#endif
