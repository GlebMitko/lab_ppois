#include "../../include/products/ProductSpecification.hpp"

namespace minimarket {
namespace products {

ProductSpecification::ProductSpecification(const std::string& id) : productId(id) {}

bool ProductSpecification::addSpecification(const std::string& key, const std::string& value) {
    if (key.empty() || value.empty()) return false;
    specifications[key] = value;
    return true;
}

std::string ProductSpecification::getSpecification(const std::string& key) const {
    auto it = specifications.find(key);
    return it != specifications.end() ? it->second : "";
}

bool ProductSpecification::meetsRequirements(const std::map<std::string, std::string>& requirements) const {
    for (const auto& [key, requiredValue] : requirements) {
        auto it = specifications.find(key);
        if (it == specifications.end() || it->second != requiredValue) {
            return false;
        }
    }
    return true;
}

} // namespace products
} // namespace minimarket
