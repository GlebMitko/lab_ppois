#pragma once
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <map>
#include "../utils/Exceptions.hpp"

namespace minimarket {
namespace orders {

// 1. Базовый класс заказа
class Order {
private:
    std::string orderId;
    std::string customerId;
    std::time_t orderDate;
    double totalAmount;
public:
    Order(const std::string& id, const std::string& custId, double amount);
    
    // Добавляем геттеры
    std::string getOrderId() const { return orderId; }
    std::string getCustomerId() const { return customerId; }
    double getTotalAmount() const { return totalAmount; }
    
    bool validateOrder() const;
    double calculateTax() const;
    std::string generateOrderSummary() const;
};

// 2. Элемент заказа
class OrderItem {
private:
    std::string productId;
    std::string productName;
    int quantity;
    double unitPrice;
public:
    OrderItem(const std::string& prodId, const std::string& name, int qty, double price);
    
    // Добавляем геттеры
    std::string getProductId() const { return productId; }
    std::string getProductName() const { return productName; }
    int getQuantity() const { return quantity; }
    double getUnitPrice() const { return unitPrice; }
    
    double calculateItemTotal() const;
    bool validateQuantity() const;
    bool applyQuantityDiscount();
};

// 3. Платежная информация
class Payment {
private:
    std::string paymentId;
    std::string orderId;
    double amount;
    std::string paymentMethod;
    std::string status;
public:
    Payment(const std::string& payId, const std::string& ordId, double amt, const std::string& method);
    
    // Добавляем геттеры
    std::string getPaymentId() const { return paymentId; }
    std::string getOrderId() const { return orderId; }
    double getAmount() const { return amount; }
    std::string getPaymentMethod() const { return paymentMethod; }
    std::string getStatus() const { return status; }
    
    bool processPayment();
    bool verifyPayment() const;
    std::string generatePaymentConfirmation() const;
};

// 4. Доставка
class Shipping {
private:
    std::string shippingId;
    std::string orderId;
    std::string address;
    std::string shippingMethod;
    std::time_t estimatedDelivery;
public:
    Shipping(const std::string& shipId, const std::string& ordId,
             const std::string& addr, const std::string& method);
    
    // Добавляем геттеры
    std::string getShippingId() const { return shippingId; }
    std::string getOrderId() const { return orderId; }
    std::string getAddress() const { return address; }
    std::string getShippingMethod() const { return shippingMethod; }
    
    bool scheduleDelivery();
    int calculateShippingDays() const;
    bool validateShippingAddress() const;
};

// 5. Корзина покупок
class ShoppingCart {
private:
    std::string cartId;
    std::string customerId;
    std::vector<std::shared_ptr<OrderItem>> items;
public:
    ShoppingCart(const std::string& id, const std::string& custId);
    
    // Добавляем геттеры
    std::string getCartId() const { return cartId; }
    std::string getCustomerId() const { return customerId; }
    
    bool addItem(const std::shared_ptr<OrderItem>& item);
    bool removeItem(const std::string& productId);
    double calculateCartTotal() const;
    bool applyCartDiscount(double discountPercent);
    std::vector<std::string> getCartItems() const;
};

} // namespace orders
} // namespace minimarket
