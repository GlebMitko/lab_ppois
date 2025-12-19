#ifndef MINIMARKET_PRODUCTS_DISCOUNTSYSTEM_HPP
#define MINIMARKET_PRODUCTS_DISCOUNTSYSTEM_HPP

#include <string>
#include <unordered_map>

namespace minimarket {
namespace products {

class DiscountSystem {
public:
    DiscountSystem(double loyaltyRate = 5.0);
    bool applyProductDiscount(const std::string& productId, double discount);
    double calculateLoyaltyDiscount(double totalAmount) const;
    bool isDiscountValid(const std::string& productId) const;

private:
    std::unordered_map<std::string, double> activeDiscounts;
    double loyaltyDiscountRate;
};

} // namespace products
} // namespace minimarket

#endif
