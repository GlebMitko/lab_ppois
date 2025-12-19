#ifndef MINIMARKET_PRODUCTS_WAREHOUSE_HPP
#define MINIMARKET_PRODUCTS_WAREHOUSE_HPP

#include <string>

namespace minimarket {
namespace products {

class Warehouse {
public:
    Warehouse(const std::string& id, const std::string& loc, double cap);
    bool allocateSpace(double requiredSpace);
    double calculateAvailableSpace() const;
    bool canStoreProduct(double productVolume) const;

    const std::string& getWarehouseId() const { return warehouseId; }
    const std::string& getLocation() const { return location; }
    double getCapacity() const { return capacity; }
    double getUsedSpace() const { return usedSpace; }

private:
    std::string warehouseId;
    std::string location;
    double capacity;
    double usedSpace;
};

} // namespace products
} // namespace minimarket

#endif
