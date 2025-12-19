#ifndef MINIMARKET_PRODUCTS_CATEGORY_HPP
#define MINIMARKET_PRODUCTS_CATEGORY_HPP

#include <string>
#include <vector>
#include <memory>
#include "Product.hpp"

namespace minimarket {
namespace products {

class Category {
public:
    Category(const std::string& id, const std::string& name);
    bool addProduct(const std::shared_ptr<Product>& product);
    double calculateCategoryRevenue() const;
    std::vector<std::string> getProductNames() const;

    const std::string& getCategoryId() const { return categoryId; }
    const std::string& getCategoryName() const { return categoryName; }

private:
    std::string categoryId;
    std::string categoryName;
    std::vector<std::shared_ptr<Product>> products;
};

} // namespace products
} // namespace minimarket

#endif
