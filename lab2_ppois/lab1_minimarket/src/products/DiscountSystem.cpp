#include "../../include/products/DiscountSystem.hpp"

namespace minimarket {
namespace products {

DiscountSystem::DiscountSystem(double loyaltyRate) : loyaltyDiscountRate(loyaltyRate) {}

bool DiscountSystem::applyProductDiscount(const std::string& productId, double discount) {
    if (discount < 0 || discount > 50) return false;
    activeDiscounts[productId] = discount;
    return true;
}

double DiscountSystem::calculateLoyaltyDiscount(double totalAmount) const {
    return totalAmount * (loyaltyDiscountRate / 100);
}

bool DiscountSystem::isDiscountValid(const std::string& productId) const {
    auto it = activeDiscounts.find(productId);
    return it != activeDiscounts.end() && it->second > 0;
}

} // namespace products
} // namespace minimarket
