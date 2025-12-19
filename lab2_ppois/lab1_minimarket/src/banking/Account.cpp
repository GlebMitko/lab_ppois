#include "../../include/banking/Account.hpp"

namespace minimarket {
namespace banking {

Account::Account(const std::string& number, const std::string& name)
    : accountNumber(number), holderName(name), balance(std::make_shared<Balance>(0.0)) {}

bool Account::transferMoney(double amount, Account& target) {
    if (!balance->withdraw(amount)) return false;
    // В реальной системе: target.balance->deposit(amount);
    return true;
}

bool Account::applyOverdraft(double limit) {
    return limit > 0;
}

double Account::calculateInterest() const {
    return balance->calculateTotal() * 0.02;
}

double Account::getAvailableBalance() const {
    return balance ? balance->getAvailableAmount() : 0.0;
}

} // namespace banking
} // namespace minimarket
