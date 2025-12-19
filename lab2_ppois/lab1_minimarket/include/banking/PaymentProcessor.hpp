#ifndef MINIMARKET_BANKING_PAYMENTPROCESSOR_HPP
#define MINIMARKET_BANKING_PAYMENTPROCESSOR_HPP

#include <string>
#include "Card.hpp"

namespace minimarket {
namespace banking {

class PaymentProcessor {
public:
    PaymentProcessor(const std::string& id, double fee);
    bool processCardPayment(const Card& card, double amount) const;
    double calculateFee(double amount) const;
    const std::string& getProcessorId() const { return processorId; }
    double getTransactionFee() const { return transactionFee; }

private:
    std::string processorId;
    double transactionFee;
};

} // namespace banking
} // namespace minimarket

#endif
