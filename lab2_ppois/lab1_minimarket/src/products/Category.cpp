#include "../../include/products/Category.hpp"

namespace minimarket {
namespace products {

Category::Category(const std::string& id, const std::string& name)
    : categoryId(id), categoryName(name) {}

bool Category::addProduct(const std::shared_ptr<Product>& product) {
    if (!product) return false;
    products.push_back(product);
    return true;
}

double Category::calculateCategoryRevenue() const {
    double total = 0.0;
    for (const auto& product : products) {
        total += product->calculateFinalPrice();
    }
    return total;
}

std::vector<std::string> Category::getProductNames() const {
    std::vector<std::string> names;
    for (const auto& product : products) {
        names.push_back(product->getProductInfo());
    }
    return names;
}

} // namespace products
} // namespace minimarket
