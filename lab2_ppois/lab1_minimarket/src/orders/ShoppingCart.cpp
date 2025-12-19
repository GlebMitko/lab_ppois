#include "../../include/orders/ShoppingCart.hpp"
#include <algorithm>

namespace minimarket {
namespace orders {

ShoppingCart::ShoppingCart(const std::string& id, const std::string& custId)
    : cartId(id), customerId(custId) {}

bool ShoppingCart::addItem(const std::shared_ptr<OrderItem>& item) {
    if (!item || !item->validateQuantity()) return false;
    
    for (const auto& existingItem : items) {
        if (existingItem->getProductId() == item->getProductId()) {
            return false;
        }
    }
    
    items.push_back(item);
    return true;
}

bool ShoppingCart::removeItem(const std::string& productId) {
    auto it = std::remove_if(items.begin(), items.end(),
        [&](const auto& item) { return item->getProductId() == productId; });
    
    bool removed = it != items.end();
    items.erase(it, items.end());
    return removed;
}

double ShoppingCart::calculateCartTotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item->calculateItemTotal();
    }
    return total;
}

bool ShoppingCart::applyCartDiscount(double discountPercent) {
    if (discountPercent < 0 || discountPercent > 50) return false;
    for (auto& item : items) {
        if (item->getQuantity() >= 5) {
            discountPercent += 5;
        }
    }
    return true;
}

std::vector<std::string> ShoppingCart::getCartItems() const {
    std::vector<std::string> itemList;
    for (const auto& item : items) {
        itemList.push_back(item->getProductName() + " x" + std::to_string(item->getQuantity()));
    }
    return itemList;
}

} // namespace orders
} // namespace minimarket
