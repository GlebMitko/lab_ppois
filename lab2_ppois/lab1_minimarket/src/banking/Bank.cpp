#include "../../include/banking/Bank.hpp"
#include <algorithm>

namespace minimarket {
namespace banking {

Bank::Bank(const std::string& code, const std::string& name)
    : bankCode(code), bankName(name) {}

std::string Bank::getBankCode() const { return bankCode; }
std::string Bank::getBankName() const { return bankName; }

bool Bank::addAccount(const std::shared_ptr<Account>& account) {
    if (!account) return false;
    accounts.push_back(account);
    return true;
}

bool Bank::openAccount(const std::string& holderName) {
    if (holderName.empty()) return false;
    std::string accountNumber = "ACC" + std::to_string(accounts.size() + 1);
    accounts.push_back(std::make_shared<Account>(accountNumber, holderName));
    return true;
}

bool Bank::closeAccount(const std::string& accountNumber) {
    auto it = std::remove_if(accounts.begin(), accounts.end(),
        [&](const auto& acc) { return acc->getAccountNumber() == accountNumber; });
    bool found = it != accounts.end();
    accounts.erase(it, accounts.end());
    return found;
}

double Bank::calculateTotalAssets() const {
    double total = 0.0;
    for (const auto& account : accounts) {
        total += account->getAvailableBalance();
    }
    return total;
}

size_t Bank::getTotalAccountsCount() const {
    return accounts.size();
}

} // namespace banking
} // namespace minimarket
