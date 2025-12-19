#ifndef MINIMARKET_PRODUCTS_INVENTORY_HPP
#define MINIMARKET_PRODUCTS_INVENTORY_HPP

#include <string>
#include <vector>
#include <unordered_map>

namespace minimarket {
namespace products {

class Inventory {
public:
    Inventory(int threshold = 10);
    bool updateStock(const std::string& productId, int quantity);
    bool checkAvailability(const std::string& productId, int requested) const;
    std::vector<std::string> getLowStockProducts() const;

private:
    std::unordered_map<std::string, int> stockLevels;
    int lowStockThreshold;
};

} // namespace products
} // namespace minimarket

#endif
