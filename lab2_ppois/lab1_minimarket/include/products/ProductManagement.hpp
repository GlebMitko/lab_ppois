#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "../utils/Exceptions.hpp"

namespace minimarket {
namespace products {

// 1. Базовый класс товара
class Product {
private:
    std::string productId;
    std::string productName;
    double basePrice;
public:
    Product(const std::string& id, const std::string& name, double price);
    
    // Добавляем геттеры
    std::string getProductId() const { return productId; }
    std::string getProductName() const { return productName; }
    double getBasePrice() const { return basePrice; }
    
    virtual double calculateFinalPrice() const;
    bool applyDiscount(double discountPercent);
    virtual std::string getProductInfo() const;
};

// 2. Категория товаров
class Category {
private:
    std::string categoryId;
    std::string categoryName;
    std::vector<std::shared_ptr<Product>> products;
public:
    Category(const std::string& id, const std::string& name);
    
    // Добавляем геттеры
    std::string getCategoryId() const { return categoryId; }
    std::string getCategoryName() const { return categoryName; }
    
    bool addProduct(const std::shared_ptr<Product>& product);
    double calculateCategoryRevenue() const;
    std::vector<std::string> getProductNames() const;
};

// 3. Управление запасами
class Inventory {
private:
    std::map<std::string, int> stockLevels;
    int lowStockThreshold;
public:
    Inventory(int threshold = 10);
    bool updateStock(const std::string& productId, int quantity); // Уникальное поведение 61
    bool checkAvailability(const std::string& productId, int requested) const; // Уникальное поведение 62
    std::vector<std::string> getLowStockProducts() const; // Уникальное поведение 63
};

// 4. Ценовая политика
class PricingStrategy {
private:
    std::string strategyType;
    double markupPercentage;
public:
    PricingStrategy(const std::string& type, double markup);
    double applyPricing(double costPrice) const;    // Уникальное поведение 64
    bool validatePricing(double cost, double selling) const; // Уникальное поведение 65
};

// 5. Система скидок
class DiscountSystem {
private:
    std::map<std::string, double> activeDiscounts;
    double loyaltyDiscountRate;
public:
    DiscountSystem(double loyaltyRate = 5.0);
    bool applyProductDiscount(const std::string& productId, double discount); // Уникальное поведение 66
    double calculateLoyaltyDiscount(double totalAmount) const; // Уникальное поведение 67
    bool isDiscountValid(const std::string& productId) const; // Уникальное поведение 68
};

// 6. Поставщик
class Supplier {
private:
    std::string supplierId;
    std::string supplierName;
    std::vector<std::string> suppliedProducts;
public:
    Supplier(const std::string& id, const std::string& name);
    
    // Добавляем геттеры
    std::string getSupplierId() const { return supplierId; }
    std::string getSupplierName() const { return supplierName; }
    
    bool addSuppliedProduct(const std::string& productId);
    bool canSupplyProduct(const std::string& productId) const;
    int getSuppliedProductsCount() const;
};

// 7. Склад
class Warehouse {
private:
    std::string warehouseId;
    std::string location;
    double capacity;
    double usedSpace;
public:
    Warehouse(const std::string& id, const std::string& loc, double cap);
    
    // Добавляем геттеры
    std::string getWarehouseId() const { return warehouseId; }
    std::string getLocation() const { return location; }
    double getCapacity() const { return capacity; }
    
    bool allocateSpace(double requiredSpace);
    double calculateAvailableSpace() const;
    bool canStoreProduct(double productVolume) const;
};

// 8. Штрих-код
class BarcodeSystem {
private:
    std::map<std::string, std::string> barcodeDatabase;
public:
    BarcodeSystem();
    bool registerBarcode(const std::string& productId, const std::string& barcode); // Уникальное поведение 75
    std::string findProductByBarcode(const std::string& barcode) const; // Уникальное поведение 76
    bool validateBarcode(const std::string& barcode) const; // Уникальное поведение 77
};

// 9. Отзывы о товарах
class ProductReview {
private:
    std::string reviewId;
    std::string productId;
    int rating;
    std::string comment;
public:
    ProductReview(const std::string& id, const std::string& prodId, int rate, const std::string& cmt);
    
    // Добавляем геттеры
    std::string getReviewId() const { return reviewId; }
    std::string getProductId() const { return productId; }
    int getRating() const { return rating; }
    std::string getComment() const { return comment; }
    
    bool validateRating() const;
    double calculateReviewImpact() const;
    std::string generateSummary() const;
};

// 10. Спецификация товара
class ProductSpecification {
private:
    std::string productId;
    std::map<std::string, std::string> specifications;
public:
    ProductSpecification(const std::string& id);
    bool addSpecification(const std::string& key, const std::string& value); // Уникальное поведение 81
    std::string getSpecification(const std::string& key) const; // Уникальное поведение 82
    bool meetsRequirements(const std::map<std::string, std::string>& requirements) const; // Уникальное поведение 83
};

} // namespace products
} // namespace minimarket
