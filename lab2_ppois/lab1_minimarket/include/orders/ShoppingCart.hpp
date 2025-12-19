#ifndef MINIMARKET_ORDERS_SHOPPINGCART_HPP
#define MINIMARKET_ORDERS_SHOPPINGCART_HPP

#include <string>
#include <vector>
#include <memory>
#include "OrderItem.hpp"

namespace minimarket {
namespace orders {

class ShoppingCart {
public:
    ShoppingCart(const std::string& id, const std::string& custId);
    bool addItem(const std::shared_ptr<OrderItem>& item);
    bool removeItem(const std::string& productId);
    double calculateCartTotal() const;
    bool applyCartDiscount(double discountPercent);
    std::vector<std::string> getCartItems() const;

    const std::string& getCartId() const { return cartId; }
    const std::string& getCustomerId() const { return customerId; }
    const std::vector<std::shared_ptr<OrderItem>>& getItems() const { return items; }

private:
    std::string cartId;
    std::string customerId;
    std::vector<std::shared_ptr<OrderItem>> items;
};

} // namespace orders
} // namespace minimarket

#endif
