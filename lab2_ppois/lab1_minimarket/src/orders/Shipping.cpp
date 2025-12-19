#include "../../include/orders/Shipping.hpp"

namespace minimarket {
namespace orders {

Shipping::Shipping(const std::string& shipId, const std::string& ordId,
                   const std::string& addr, const std::string& method)
    : shippingId(shipId), orderId(ordId), address(addr), shippingMethod(method) {
    std::time_t now = std::time(nullptr);
    int daysToAdd = (shippingMethod == "Express") ? 2 : 5;
    estimatedDelivery = now + (daysToAdd * 24 * 60 * 60);
}

bool Shipping::scheduleDelivery() {
    return !shippingId.empty() && !orderId.empty() && !address.empty();
}

int Shipping::calculateShippingDays() const {
    std::time_t now = std::time(nullptr);
    double secondsDiff = std::difftime(estimatedDelivery, now);
    return static_cast<int>(secondsDiff / (24 * 60 * 60));
}

bool Shipping::validateShippingAddress() const {
    return !address.empty() && address.length() >= 10 &&
           address.find("Street") != std::string::npos;
}

} // namespace orders
} // namespace minimarket
