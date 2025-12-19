#include "../../include/orders/Order.hpp"
#include "../../include/utils/Exceptions.hpp"

namespace minimarket {
namespace orders {

Order::Order(const std::string& id, const std::string& custId, double amount)
    : orderId(id), customerId(custId), orderDate(std::time(nullptr)), totalAmount(amount) {
    if (amount < 0) throw exceptions::InvalidOperationException("Order amount cannot be negative");
}

bool Order::validateOrder() const {
    return !orderId.empty() && !customerId.empty() && totalAmount > 0;
}

double Order::calculateTax() const {
    return totalAmount * 0.08;
}

std::string Order::generateOrderSummary() const {
    return "Order #" + orderId + " - Total: $" + std::to_string(totalAmount) +
           " - Tax: $" + std::to_string(calculateTax());
}

} // namespace orders
} // namespace minimarket
