#ifndef MINIMARKET_BANKING_BANKSTATEMENT_HPP
#define MINIMARKET_BANKING_BANKSTATEMENT_HPP

#include <string>
#include <vector>
#include <ctime>
#include "Transaction.hpp"

namespace minimarket {
namespace banking {

class BankStatement {
public:
    BankStatement(const std::string& accNumber, std::time_t start, std::time_t end);
    double calculateEndingBalance() const;
    void generatePDFReport() const;
    void addTransaction(const Transaction& transaction) { transactions.push_back(transaction); }
    const std::string& getAccountNumber() const { return accountNumber; }
    std::time_t getPeriodStart() const { return periodStart; }
    std::time_t getPeriodEnd() const { return periodEnd; }

private:
    std::string accountNumber;
    std::time_t periodStart;
    std::time_t periodEnd;
    std::vector<Transaction> transactions;
};

} // namespace banking
} // namespace minimarket

#endif
