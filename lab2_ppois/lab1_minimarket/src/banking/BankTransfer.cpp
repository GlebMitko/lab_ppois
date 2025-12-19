#include "../../include/banking/BankTransfer.hpp"

namespace minimarket {
namespace banking {

BankTransfer::BankTransfer(const std::string& id, double amt,
                           const std::string& from, const std::string& to)
    : transferId(id), amount(amt), fromAccount(from), toAccount(to) {}

bool BankTransfer::executeTransfer() {
    return validateAccounts() && amount > 0 && amount <= 50000;
}

bool BankTransfer::validateAccounts() const {
    return !fromAccount.empty() && !toAccount.empty() && fromAccount != toAccount;
}

} // namespace banking
} // namespace minimarket
