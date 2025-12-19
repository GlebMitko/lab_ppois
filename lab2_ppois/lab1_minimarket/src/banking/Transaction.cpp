#include "../../include/banking/Transaction.hpp"

namespace minimarket {
namespace banking {

Transaction::Transaction(const std::string& id, double amt, const std::string& tp)
    : transactionId(id), amount(amt), type(tp), timestamp(std::time(nullptr)) {
    if (amt <= 0) throw exceptions::InvalidOperationException("Transaction amount must be positive");
}

bool Transaction::validateTransaction() const {
    return !transactionId.empty() && amount > 0 && !type.empty();
}

std::string Transaction::generateReceipt() const {
    return "Receipt for " + std::to_string(amount) + " - " + type + " - ID: " + transactionId;
}

} // namespace banking
} // namespace minimarket
