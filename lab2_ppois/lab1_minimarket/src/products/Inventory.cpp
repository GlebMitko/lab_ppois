#include "../../include/products/Inventory.hpp"

namespace minimarket {
namespace products {

Inventory::Inventory(int threshold) : lowStockThreshold(threshold) {}

bool Inventory::updateStock(const std::string& productId, int quantity) {
    if (productId.empty()) return false;
    stockLevels[productId] += quantity;
    return true;
}

bool Inventory::checkAvailability(const std::string& productId, int requested) const {
    auto it = stockLevels.find(productId);
    if (it == stockLevels.end()) return false;
    return it->second >= requested;
}

std::vector<std::string> Inventory::getLowStockProducts() const {
    std::vector<std::string> lowStock;
    for (const auto& [productId, quantity] : stockLevels) {
        if (quantity <= lowStockThreshold) {
            lowStock.push_back(productId);
        }
    }
    return lowStock;
}

} // namespace products
} // namespace minimarket
