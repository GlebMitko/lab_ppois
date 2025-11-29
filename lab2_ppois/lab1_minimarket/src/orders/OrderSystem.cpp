#include "../../include/orders/OrderSystem.hpp"
#include "../../include/utils/Exceptions.hpp"
#include <algorithm>

namespace minimarket {
namespace orders {

// Order implementation
Order::Order(const std::string& id, const std::string& custId, double amount)
    : orderId(id), customerId(custId), orderDate(std::time(nullptr)), totalAmount(amount) {
    if (amount < 0) throw exceptions::InvalidOperationException("Order amount cannot be negative");
}

bool Order::validateOrder() const {
    return !orderId.empty() && !customerId.empty() && totalAmount > 0;
}

double Order::calculateTax() const {
    return totalAmount * 0.08; // 8% налог
}

std::string Order::generateOrderSummary() const {
    return "Order #" + orderId + " - Total: $" + std::to_string(totalAmount) +
           " - Tax: $" + std::to_string(calculateTax());
}

// OrderItem implementation
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
        // unitPrice *= 0.9; // 10% скидка за 10+ штук
        return true;
    }
    return false;
}

// Payment implementation
Payment::Payment(const std::string& payId, const std::string& ordId, double amt, const std::string& method)
    : paymentId(payId), orderId(ordId), amount(amt), paymentMethod(method), status("Pending") {}

bool Payment::processPayment() {
    if (amount <= 0) return false;
    
    // Упрощенная логика обработки платежа
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

// Shipping implementation
Shipping::Shipping(const std::string& shipId, const std::string& ordId,
                   const std::string& addr, const std::string& method)
    : shippingId(shipId), orderId(ordId), address(addr), shippingMethod(method) {
    // Расчет предполагаемой даты доставки
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

// ShoppingCart implementation
ShoppingCart::ShoppingCart(const std::string& id, const std::string& custId)
    : cartId(id), customerId(custId) {}

bool ShoppingCart::addItem(const std::shared_ptr<OrderItem>& item) {
    if (!item || !item->validateQuantity()) return false;
    
    // Проверяем нет ли уже этого товара в корзине
    for (const auto& existingItem : items) {
        if (existingItem->getProductId() == item->getProductId()) {
            return false; // Товар уже в корзине
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
    
    // Применяем скидку к каждому товару
    for (auto& item : items) {
        // Упрощенная логика применения скидки
        if (item->getQuantity() >= 5) {
            // Дополнительная скидка за количество
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
