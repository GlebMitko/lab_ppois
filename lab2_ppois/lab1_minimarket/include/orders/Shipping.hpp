#ifndef MINIMARKET_ORDERS_SHIPPING_HPP
#define MINIMARKET_ORDERS_SHIPPING_HPP

#include <string>
#include <ctime>

namespace minimarket {
namespace orders {

class Shipping {
public:
    Shipping(const std::string& shipId, const std::string& ordId, const std::string& addr, const std::string& method);
    bool scheduleDelivery();
    int calculateShippingDays() const;
    bool validateShippingAddress() const;

    const std::string& getShippingId() const { return shippingId; }
    const std::string& getOrderId() const { return orderId; }
    const std::string& getAddress() const { return address; }
    const std::string& getShippingMethod() const { return shippingMethod; }
    std::time_t getEstimatedDelivery() const { return estimatedDelivery; }

private:
    std::string shippingId;
    std::string orderId;
    std::string address;
    std::string shippingMethod;
    std::time_t estimatedDelivery;
};

} // namespace orders
} // namespace minimarket

#endif
