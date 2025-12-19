#ifndef MINIMARKET_ORDERS_ORDER_HPP
#define MINIMARKET_ORDERS_ORDER_HPP

#include <string>
#include <ctime>

namespace minimarket {
namespace orders {

class Order {
public:
    Order(const std::string& id, const std::string& custId, double amount);
    bool validateOrder() const;
    double calculateTax() const;
    std::string generateOrderSummary() const;

    const std::string& getOrderId() const { return orderId; }
    const std::string& getCustomerId() const { return customerId; }
    double getTotalAmount() const { return totalAmount; }
    std::time_t getOrderDate() const { return orderDate; }

private:
    std::string orderId;
    std::string customerId;
    std::time_t orderDate;
    double totalAmount;
};

} // namespace orders
} // namespace minimarket

#endif
