#include "../../include/banking/Balance.hpp"

namespace minimarket {
namespace banking {

Balance::Balance(double amount, const std::string& currency)
    : availableAmount(amount), reservedAmount(0.0), currencyCode(currency) {
    if (amount < 0) throw exceptions::InvalidOperationException("Balance cannot be negative");
}

bool Balance::withdraw(double amount) {
    if (amount <= 0 || amount > availableAmount) return false;
    availableAmount -= amount;
    return true;
}

void Balance::reserveFunds(double amount) {
    if (amount <= 0 || amount > availableAmount) {
        throw exceptions::InsufficientFundsException("Cannot reserve funds");
    }
    availableAmount -= amount;
    reservedAmount += amount;
}

double Balance::calculateTotal() const {
    return availableAmount + reservedAmount;
}


} // namespace banking
} // namespace minimarket
