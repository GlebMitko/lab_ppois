#include "../../include/banking/BankStatement.hpp"

namespace minimarket {
namespace banking {

BankStatement::BankStatement(const std::string& accNumber, std::time_t start, std::time_t end)
    : accountNumber(accNumber), periodStart(start), periodEnd(end) {}

double BankStatement::calculateEndingBalance() const {
    double balance = 0.0;
    for (const auto& transaction : transactions) {
        balance += transaction.getAmount();
    }
    return balance;
}

void BankStatement::generatePDFReport() const {
    // Stub
}

} // namespace banking
} // namespace minimarket
