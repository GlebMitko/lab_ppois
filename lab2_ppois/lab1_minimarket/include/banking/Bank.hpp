#ifndef MINIMARKET_BANKING_BANK_HPP
#define MINIMARKET_BANKING_BANK_HPP

#include <string>
#include <vector>
#include <memory>
#include "Account.hpp"

namespace minimarket {
namespace banking {

class Bank {
public:
    Bank(const std::string& code, const std::string& name);
    std::string getBankCode() const;
    std::string getBankName() const;
    bool addAccount(const std::shared_ptr<Account>& account);
    bool openAccount(const std::string& holderName);
    bool closeAccount(const std::string& accountNumber);
    double calculateTotalAssets() const;
    size_t getTotalAccountsCount() const;

private:
    std::string bankCode;
    std::string bankName;
    std::vector<std::shared_ptr<Account>> accounts;
};

} // namespace banking
} // namespace minimarket

#endif
