#ifndef MINIMARKET_BANKING_CURRENCYCONVERTER_HPP
#define MINIMARKET_BANKING_CURRENCYCONVERTER_HPP

#include <string>
#include <unordered_map>

namespace minimarket {
namespace banking {

class CurrencyConverter {
public:
    CurrencyConverter();
    double convertAmount(double amount, const std::string& from, const std::string& to) const;
    void updateExchangeRate(const std::string& currency, double rate);
    double getRate(const std::string& currency) const;

private:
    mutable std::unordered_map<std::string, double> exchangeRates;
};

} // namespace banking
} // namespace minimarket

#endif
