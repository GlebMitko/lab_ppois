#ifndef MINIMARKET_BANKING_TRANSACTION_HPP
#define MINIMARKET_BANKING_TRANSACTION_HPP

#include <string>
#include <ctime>
#include "../../include/utils/Exceptions.hpp"

namespace minimarket {
namespace banking {

class Transaction {
public:
    Transaction(const std::string& id, double amt, const std::string& tp);
    bool validateTransaction() const;
    std::string generateReceipt() const;
    double getAmount() const { return amount; }
    const std::string& getTransactionId() const { return transactionId; }
    const std::string& getType() const { return type; }
    std::time_t getTimestamp() const { return timestamp; }

private:
    std::string transactionId;
    double amount;
    std::string type;
    std::time_t timestamp;
};

} // namespace banking
} // namespace minimarket

#endif
