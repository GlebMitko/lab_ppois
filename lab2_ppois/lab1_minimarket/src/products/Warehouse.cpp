#include "../../include/products/Warehouse.hpp"

namespace minimarket {
namespace products {

Warehouse::Warehouse(const std::string& id, const std::string& loc, double cap)
    : warehouseId(id), location(loc), capacity(cap), usedSpace(0.0) {}

bool Warehouse::allocateSpace(double requiredSpace) {
    if (requiredSpace <= 0 || usedSpace + requiredSpace > capacity) return false;
    usedSpace += requiredSpace;
    return true;
}

double Warehouse::calculateAvailableSpace() const {
    return capacity - usedSpace;
}

bool Warehouse::canStoreProduct(double productVolume) const {
    return productVolume > 0 && productVolume <= calculateAvailableSpace();
}

} // namespace products
} // namespace minimarket
