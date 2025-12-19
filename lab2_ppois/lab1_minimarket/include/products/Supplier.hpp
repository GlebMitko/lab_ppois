#ifndef MINIMARKET_PRODUCTS_SUPPLIER_HPP
#define MINIMARKET_PRODUCTS_SUPPLIER_HPP

#include <string>
#include <vector>

namespace minimarket {
namespace products {

class Supplier {
public:
    Supplier(const std::string& id, const std::string& name);
    bool addSuppliedProduct(const std::string& productId);
    bool canSupplyProduct(const std::string& productId) const;
    int getSuppliedProductsCount() const;

    const std::string& getSupplierId() const { return supplierId; }
    const std::string& getSupplierName() const { return supplierName; }

private:
    std::string supplierId;
    std::string supplierName;
    std::vector<std::string> suppliedProducts;
};

} // namespace products
} // namespace minimarket

#endif
