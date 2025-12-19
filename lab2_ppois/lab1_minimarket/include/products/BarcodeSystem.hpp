#ifndef MINIMARKET_PRODUCTS_BARCODESYSTEM_HPP
#define MINIMARKET_PRODUCTS_BARCODESYSTEM_HPP

#include <string>
#include <unordered_map>

namespace minimarket {
namespace products {

class BarcodeSystem {
public:
    BarcodeSystem();
    bool registerBarcode(const std::string& productId, const std::string& barcode);
    std::string findProductByBarcode(const std::string& barcode) const;
    bool validateBarcode(const std::string& barcode) const;

private:
    std::unordered_map<std::string, std::string> barcodeDatabase;
};

} // namespace products
} // namespace minimarket

#endif
