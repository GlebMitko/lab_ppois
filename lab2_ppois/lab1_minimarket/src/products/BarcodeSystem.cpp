#include "../../include/products/BarcodeSystem.hpp"
#include <cctype>

namespace minimarket {
namespace products {

BarcodeSystem::BarcodeSystem() {
    barcodeDatabase["123456789012"] = "PROD001";
    barcodeDatabase["987654321098"] = "PROD002";
}

bool BarcodeSystem::registerBarcode(const std::string& productId, const std::string& barcode) {
    if (productId.empty() || barcode.empty() || barcode.length() != 12) return false;
    barcodeDatabase[barcode] = productId;
    return true;
}

std::string BarcodeSystem::findProductByBarcode(const std::string& barcode) const {
    auto it = barcodeDatabase.find(barcode);
    return it != barcodeDatabase.end() ? it->second : "";
}

bool BarcodeSystem::validateBarcode(const std::string& barcode) const {
    if (barcode.length() != 12) return false;
    for (char c : barcode) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

} // namespace products
} // namespace minimarket
