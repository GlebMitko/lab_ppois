#ifndef MINIMARKET_BANKING_BANKTRANSFER_HPP
#define MINIMARKET_BANKING_BANKTRANSFER_HPP

#include <string>

namespace minimarket {
namespace banking {

class BankTransfer {
public:
    BankTransfer(const std::string& id, double amt, const std::string& from, const std::string& to);
    bool executeTransfer();
    bool validateAccounts() const;
    const std::string& getTransferId() const { return transferId; }
    double getAmount() const { return amount; }
    const std::string& getFromAccount() const { return fromAccount; }
    const std::string& getToAccount() const { return toAccount; }

private:
    std::string transferId;
    double amount;
    std::string fromAccount;
    std::string toAccount;
};

} // namespace banking
} // namespace minimarket

#endif
