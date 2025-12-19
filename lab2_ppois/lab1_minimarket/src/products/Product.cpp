#include "../../include/products/Product.hpp"
#include "../../include/utils/Exceptions.hpp"

namespace minimarket {
namespace products {

Product::Product(const std::string& id, const std::string& name, double price)
    : productId(id), productName(name), basePrice(price) {
    if (price < 0) throw exceptions::InvalidOperationException("Price cannot be negative");
}

double Product::calculateFinalPrice() const {
    return basePrice * 1.2;
}

bool Product::applyDiscount(double discountPercent) {
    if (discountPercent < 0 || discountPercent > 100) return false;
    basePrice *= (1 - discountPercent / 100);
    return true;
}

std::string Product::getProductInfo() const {
    return productName + " (ID: " + productId + ") - $" + std::to_string(basePrice);
}

} // namespace products
} // namespace minimarket
