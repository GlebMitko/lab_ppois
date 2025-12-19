#ifndef MINIMARKET_ORDERS_ORDERITEM_HPP
#define MINIMARKET_ORDERS_ORDERITEM_HPP

#include <string>
#include <memory>

namespace minimarket {
namespace orders {

class OrderItem {
public:
    OrderItem(const std::string& prodId, const std::string& name, int qty, double price);
    double calculateItemTotal() const;
    bool validateQuantity() const;
    bool applyQuantityDiscount();

    const std::string& getProductId() const { return productId; }
    const std::string& getProductName() const { return productName; }
    int getQuantity() const { return quantity; }
    double getUnitPrice() const { return unitPrice; }

private:
    std::string productId;
    std::string productName;
    int quantity;
    double unitPrice;
};

} // namespace orders
} // namespace minimarket

#endif
