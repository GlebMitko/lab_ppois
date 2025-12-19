#ifndef MINIMARKET_BANKING_ACCOUNT_HPP
#define MINIMARKET_BANKING_ACCOUNT_HPP

#include <string>
#include <memory>
#include "Balance.hpp"

namespace minimarket {
namespace banking {

class Account {
public:
    Account(const std::string& number, const std::string& name);
    bool transferMoney(double amount, Account& target);
    bool applyOverdraft(double limit);
    double calculateInterest() const;
    double getAvailableBalance() const;
    const std::string& getAccountNumber() const { return accountNumber; }
    const std::string& getHolderName() const { return holderName; }

protected:
    std::string accountNumber;
    std::string holderName;
    std::shared_ptr<Balance> balance;
};

} // namespace banking
} // namespace minimarket

#endif
