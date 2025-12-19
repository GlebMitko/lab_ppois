#include "../../include/banking/CreditCard.hpp"

namespace minimarket {
namespace banking {

bool CreditCard::useCredit(double amount) {
    if (amount <= 0 || usedCredit + amount > creditLimit) return false;
    usedCredit += amount;
    return true;
}

double CreditCard::calculateAvailableCredit() const {
    return creditLimit - usedCredit;
}

} // namespace banking
} // namespace minimarket
