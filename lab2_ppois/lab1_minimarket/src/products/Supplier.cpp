#include "../../include/products/Supplier.hpp"
#include <algorithm>

namespace minimarket {
namespace products {

Supplier::Supplier(const std::string& id, const std::string& name)
    : supplierId(id), supplierName(name) {}

bool Supplier::addSuppliedProduct(const std::string& productId) {
    if (productId.empty()) return false;
    suppliedProducts.push_back(productId);
    return true;
}

bool Supplier::canSupplyProduct(const std::string& productId) const {
    return std::find(suppliedProducts.begin(), suppliedProducts.end(), productId) != suppliedProducts.end();
}

int Supplier::getSuppliedProductsCount() const {
    return suppliedProducts.size();
}

} // namespace products
} // namespace minimarket
