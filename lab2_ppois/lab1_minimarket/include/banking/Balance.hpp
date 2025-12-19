#ifndef MINIMARKET_BANKING_BALANCE_HPP
#define MINIMARKET_BANKING_BALANCE_HPP

#include <string>
#include "../../include/utils/Exceptions.hpp"

namespace minimarket {
namespace banking {

class Balance {
public:
    Balance(double amount, const std::string& currency = "USD");
    bool withdraw(double amount);
    void reserveFunds(double amount);
    double calculateTotal() const;
    double getAvailableAmount() const { return availableAmount; }
    double getReservedAmount() const { return reservedAmount; }
    const std::string& getCurrencyCode() const { return currencyCode; }

private:
    double availableAmount;
    double reservedAmount;
    std::string currencyCode;
};

} // namespace banking
} // namespace minimarket

#endif
