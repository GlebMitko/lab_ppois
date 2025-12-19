#ifndef MINIMARKET_PRODUCTS_PRODUCTSPECIFICATION_HPP
#define MINIMARKET_PRODUCTS_PRODUCTSPECIFICATION_HPP

#include <string>
#include <map>

namespace minimarket {
namespace products {

class ProductSpecification {
public:
    ProductSpecification(const std::string& id);
    bool addSpecification(const std::string& key, const std::string& value);
    std::string getSpecification(const std::string& key) const;
    bool meetsRequirements(const std::map<std::string, std::string>& requirements) const;

    const std::string& getProductId() const { return productId; }

private:
    std::string productId;
    std::map<std::string, std::string> specifications;
};

} // namespace products
} // namespace minimarket

#endif
