#include "../../include/products/ProductManagement.hpp"
#include "../../include/utils/Exceptions.hpp"
#include <algorithm>
#include <cmath>

namespace minimarket {
namespace products {

// 1. Product implementation
Product::Product(const std::string& id, const std::string& name, double price)
    : productId(id), productName(name), basePrice(price) {
    if (price < 0) throw exceptions::InvalidOperationException("Price cannot be negative");
}

double Product::calculateFinalPrice() const {
    return basePrice * 1.2; // 20% налог
}

bool Product::applyDiscount(double discountPercent) {
    if (discountPercent < 0 || discountPercent > 100) return false;
    basePrice *= (1 - discountPercent / 100);
    return true;
}

std::string Product::getProductInfo() const {
    return productName + " (ID: " + productId + ") - $" + std::to_string(basePrice);
}

// 2. Category implementation
Category::Category(const std::string& id, const std::string& name)
    : categoryId(id), categoryName(name) {}

bool Category::addProduct(const std::shared_ptr<Product>& product) {
    if (!product) return false;
    products.push_back(product);
    return true;
}

double Category::calculateCategoryRevenue() const {
    double total = 0.0;
    for (const auto& product : products) {
        total += product->calculateFinalPrice();
    }
    return total;
}

std::vector<std::string> Category::getProductNames() const {
    std::vector<std::string> names;
    for (const auto& product : products) {
        names.push_back(product->getProductInfo());
    }
    return names;
}

// 3. Inventory implementation
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

// 4. PricingStrategy implementation
PricingStrategy::PricingStrategy(const std::string& type, double markup)
    : strategyType(type), markupPercentage(markup) {}

double PricingStrategy::applyPricing(double costPrice) const {
    return costPrice * (1 + markupPercentage / 100);
}

bool PricingStrategy::validatePricing(double cost, double selling) const {
    return selling >= cost && selling <= cost * 3; // Максимум 300% наценки
}

// 5. DiscountSystem implementation
DiscountSystem::DiscountSystem(double loyaltyRate) : loyaltyDiscountRate(loyaltyRate) {}

bool DiscountSystem::applyProductDiscount(const std::string& productId, double discount) {
    if (discount < 0 || discount > 50) return false; // Максимум 50% скидка
    activeDiscounts[productId] = discount;
    return true;
}

double DiscountSystem::calculateLoyaltyDiscount(double totalAmount) const {
    return totalAmount * (loyaltyDiscountRate / 100);
}

bool DiscountSystem::isDiscountValid(const std::string& productId) const {
    auto it = activeDiscounts.find(productId);
    return it != activeDiscounts.end() && it->second > 0;
}

// 6. Supplier implementation
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

// 7. Warehouse implementation
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

// 8. BarcodeSystem implementation
BarcodeSystem::BarcodeSystem() {
    // Инициализация тестовыми данными
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

// 9. ProductReview implementation
ProductReview::ProductReview(const std::string& id, const std::string& prodId, int rate, const std::string& cmt)
    : reviewId(id), productId(prodId), rating(rate), comment(cmt) {}

bool ProductReview::validateRating() const {
    return rating >= 1 && rating <= 5;
}

double ProductReview::calculateReviewImpact() const {
    return rating * 0.2; // Влияние на рейтинг товара
}

std::string ProductReview::generateSummary() const {
    return "Rating: " + std::to_string(rating) + "/5 - " + comment.substr(0, 50) + "...";
}

// 10. ProductSpecification implementation
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
