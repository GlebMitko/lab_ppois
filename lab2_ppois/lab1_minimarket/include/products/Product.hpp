#ifndef MINIMARKET_PRODUCTS_PRODUCT_HPP
#define MINIMARKET_PRODUCTS_PRODUCT_HPP

#include <string>

namespace minimarket {
namespace products {

class Product {
public:
    Product(const std::string& id, const std::string& name, double price);
    double calculateFinalPrice() const;
    bool applyDiscount(double discountPercent);
    std::string getProductInfo() const;

    const std::string& getProductId() const { return productId; }
    const std::string& getProductName() const { return productName; }
    double getBasePrice() const { return basePrice; }

private:
    std::string productId;
    std::string productName;
    double basePrice;
};

} // namespace products
} // namespace minimarket

#endif
