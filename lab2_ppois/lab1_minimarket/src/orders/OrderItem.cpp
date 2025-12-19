#include "../../include/orders/OrderItem.hpp"
#include "../../include/utils/Exceptions.hpp"

namespace minimarket {
namespace orders {

OrderItem::OrderItem(const std::string& prodId, const std::string& name, int qty, double price)
    : productId(prodId), productName(name), quantity(qty), unitPrice(price) {
    if (qty <= 0) throw exceptions::InvalidOperationException("Quantity must be positive");
}

double OrderItem::calculateItemTotal() const {
    return quantity * unitPrice;
}

bool OrderItem::validateQuantity() const {
    return quantity > 0 && quantity <= 100;
}

bool OrderItem::applyQuantityDiscount() {
    if (quantity >= 10) {
        return true;
    }
    return false;
}

} // namespace orders
} // namespace minimarket
