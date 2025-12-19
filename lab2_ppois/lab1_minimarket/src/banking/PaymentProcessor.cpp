#include "../../include/banking/PaymentProcessor.hpp"

namespace minimarket {
namespace banking {

PaymentProcessor::PaymentProcessor(const std::string& id, double fee)
    : processorId(id), transactionFee(fee) {}

bool PaymentProcessor::processCardPayment(const Card& card, double amount) const {
    return card.processPayment(amount) && amount > 0;
}

double PaymentProcessor::calculateFee(double amount) const {
    return amount * transactionFee;
}

} // namespace banking
} // namespace minimarket
