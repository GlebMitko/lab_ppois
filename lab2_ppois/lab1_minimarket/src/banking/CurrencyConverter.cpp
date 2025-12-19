#include "../../include/banking/CurrencyConverter.hpp"

namespace minimarket {
namespace banking {

CurrencyConverter::CurrencyConverter() {
    exchangeRates = {{"USD", 1.0}, {"EUR", 0.85}, {"GBP", 0.75}};
}

double CurrencyConverter::convertAmount(double amount, const std::string& from,
                                       const std::string& to) const {
    auto fromIt = exchangeRates.find(from);
    auto toIt = exchangeRates.find(to);
    if (fromIt == exchangeRates.end() || toIt == exchangeRates.end()) return 0.0;
    return amount * toIt->second / fromIt->second;
}

void CurrencyConverter::updateExchangeRate(const std::string& currency, double rate) {
    exchangeRates[currency] = rate;
}

double CurrencyConverter::getRate(const std::string& currency) const {
    auto it = exchangeRates.find(currency);
    return it != exchangeRates.end() ? it->second : 0.0;
}

} // namespace banking
} // namespace minimarket
