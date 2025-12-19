#include "../../include/orders/Payment.hpp"

namespace minimarket {
namespace orders {

Payment::Payment(const std::string& payId, const std::string& ordId, double amt, const std::string& method)
    : paymentId(payId), orderId(ordId), amount(amt), paymentMethod(method), status("Pending") {}

bool Payment::processPayment() {
    if (amount <= 0) return false;
    
    if (paymentMethod == "CreditCard" && amount <= 5000) {
        status = "Completed";
        return true;
    } else if (paymentMethod == "BankTransfer" && amount <= 10000) {
        status = "Completed";
        return true;
    } else if (paymentMethod == "PayPal" && amount <= 2500) {
        status = "Completed";
        return true;
    }
    
    status = "Failed";
    return false;
}

bool Payment::verifyPayment() const {
    return status == "Completed" && amount > 0;
}

std::string Payment::generatePaymentConfirmation() const {
    return "Payment #" + paymentId + " - Amount: $" + std::to_string(amount) +
           " - Method: " + paymentMethod + " - Status: " + status;
}

} // namespace orders
} // namespace minimarket
