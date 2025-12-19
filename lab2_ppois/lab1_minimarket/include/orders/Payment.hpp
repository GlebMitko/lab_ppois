#ifndef MINIMARKET_ORDERS_PAYMENT_HPP
#define MINIMARKET_ORDERS_PAYMENT_HPP

#include <string>

namespace minimarket {
namespace orders {

class Payment {
public:
    Payment(const std::string& payId, const std::string& ordId, double amt, const std::string& method);
    bool processPayment();
    bool verifyPayment() const;
    std::string generatePaymentConfirmation() const;

    const std::string& getPaymentId() const { return paymentId; }
    const std::string& getOrderId() const { return orderId; }
    double getAmount() const { return amount; }
    const std::string& getPaymentMethod() const { return paymentMethod; }
    const std::string& getStatus() const { return status; }

private:
    std::string paymentId;
    std::string orderId;
    double amount;
    std::string paymentMethod;
    std::string status;
};

} // namespace orders
} // namespace minimarket

#endif
