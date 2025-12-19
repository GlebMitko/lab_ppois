// tests/test_products.cpp

#include <iostream>
#include <cassert>
#include <memory>
#include <string>
#include <map>
#include <algorithm>

// Подключаем индивидуальные заголовки
#include "../include/products/Product.hpp"
#include "../include/products/Category.hpp"
#include "../include/products/Inventory.hpp"
#include "../include/products/PricingStrategy.hpp"
#include "../include/products/DiscountSystem.hpp"
#include "../include/products/Supplier.hpp"
#include "../include/products/Warehouse.hpp"
#include "../include/products/BarcodeSystem.hpp"
#include "../include/products/ProductReview.hpp"
#include "../include/products/ProductSpecification.hpp"

#include "../include/utils/Exceptions.hpp"

void testProductCreation() {
    std::cout << "Testing Product creation..." << std::endl;
    
    minimarket::products::Product product("PROD001", "Laptop", 999.99);
    assert(product.getProductId() == "PROD001");
    assert(product.getProductName() == "Laptop");
    assert(product.getBasePrice() == 999.99);
    
    double finalPrice = product.calculateFinalPrice();
    assert(finalPrice == 1199.988); // 999.99 * 1.2
    
    std::string info = product.getProductInfo();
    assert(info.find("Laptop") != std::string::npos);
    assert(info.find("PROD001") != std::string::npos);
    assert(info.find("999.99") != std::string::npos);
    
    std::cout << "✅ testProductCreation: PASSED" << std::endl;
}

void testProductDiscounts() {
    std::cout << "Testing Product discounts..." << std::endl;
    
    minimarket::products::Product product("PROD002", "Mouse", 50.0);
    double originalPrice = product.getBasePrice();
    
    bool discountApplied = product.applyDiscount(10.0);
    assert(discountApplied == true);
    assert(product.getBasePrice() == 45.0);
    
    bool negativeDiscount = product.applyDiscount(-5.0);
    assert(negativeDiscount == false);
    
    bool excessiveDiscount = product.applyDiscount(110.0);
    assert(excessiveDiscount == false);
    
    std::cout << "✅ testProductDiscounts: PASSED" << std::endl;
}

void testCategoryManagement() {
    std::cout << "Testing Category management..." << std::endl;
    
    minimarket::products::Category category("CAT001", "Electronics");
    
    assert(category.getCategoryId() == "CAT001");
    assert(category.getCategoryName() == "Electronics");
    
    auto product1 = std::make_shared<minimarket::products::Product>("PROD003", "Tablet", 299.99);
    auto product2 = std::make_shared<minimarket::products::Product>("PROD004", "Phone", 599.99);
    
    assert(category.addProduct(product1) == true);
    assert(category.addProduct(product2) == true);
    
    double revenue = category.calculateCategoryRevenue();
    assert(revenue > 0.0);
    
    auto productNames = category.getProductNames();
    assert(productNames.size() == 2);
    
    std::cout << "✅ testCategoryManagement: PASSED" << std::endl;
}

void testCategoryRevenue() {
    std::cout << "Testing Category revenue calculation..." << std::endl;
    
    minimarket::products::Category category("CAT002", "Books");
    
    auto book1 = std::make_shared<minimarket::products::Product>("BOOK001", "Novel", 20.0);
    auto book2 = std::make_shared<minimarket::products::Product>("BOOK002", "Textbook", 80.0);
    
    category.addProduct(book1);
    category.addProduct(book2);
    
    double revenue = category.calculateCategoryRevenue();
    assert(revenue == 120.0); // (20 + 80) * 1.2
    
    std::cout << "✅ testCategoryRevenue: PASSED" << std::endl;
}

void testInventoryManagement() {
    std::cout << "Testing Inventory management..." << std::endl;
    
    minimarket::products::Inventory inventory(5);
    
    assert(inventory.updateStock("PROD005", 10) == true);
    assert(inventory.updateStock("PROD006", 3) == true);
    
    assert(inventory.checkAvailability("PROD005", 5) == true);
    assert(inventory.checkAvailability("PROD005", 15) == false);
    assert(inventory.checkAvailability("NONEXISTENT", 1) == false);
    
    auto lowStock = inventory.getLowStockProducts();
    assert(lowStock.size() == 1);
    assert(lowStock[0] == "PROD006");
    
    std::cout << "✅ testInventoryManagement: PASSED" << std::endl;
}

void testInventoryThreshold() {
    std::cout << "Testing Inventory threshold..." << std::endl;
    
    minimarket::products::Inventory inventory(3);
    
    inventory.updateStock("PROD007", 10);
    inventory.updateStock("PROD008", 3);
    inventory.updateStock("PROD009", 2);
    inventory.updateStock("PROD010", 0);
    
    auto lowStock = inventory.getLowStockProducts();
    
    assert(lowStock.size() == 3);
    assert(std::find(lowStock.begin(), lowStock.end(), "PROD008") != lowStock.end());
    assert(std::find(lowStock.begin(), lowStock.end(), "PROD009") != lowStock.end());
    assert(std::find(lowStock.begin(), lowStock.end(), "PROD010") != lowStock.end());
    
    std::cout << "✅ testInventoryThreshold: PASSED" << std::endl;
}

void testPricingStrategy() {
    std::cout << "Testing PricingStrategy..." << std::endl;
    
    minimarket::products::PricingStrategy strategy("Premium", 25.0);
    
    double sellingPrice = strategy.applyPricing(100.0);
    assert(sellingPrice == 125.0);
    
    assert(strategy.validatePricing(100.0, 125.0) == true);
    assert(strategy.validatePricing(100.0, 50.0) == false);
    assert(strategy.validatePricing(100.0, 400.0) == false);
    
    std::cout << "✅ testPricingStrategy: PASSED" << std::endl;
}

void testDiscountSystem() {
    std::cout << "Testing DiscountSystem..." << std::endl;
    
    minimarket::products::DiscountSystem discounts(5.0);
    
    assert(discounts.applyProductDiscount("PROD011", 15.0) == true);
    assert(discounts.applyProductDiscount("PROD012", 60.0) == false);
    
    double loyaltyDiscount = discounts.calculateLoyaltyDiscount(200.0);
    assert(loyaltyDiscount == 10.0);
    
    assert(discounts.isDiscountValid("PROD011") == true);
    assert(discounts.isDiscountValid("NONEXISTENT") == false);
    
    std::cout << "✅ testDiscountSystem: PASSED" << std::endl;
}

void testSupplierOperations() {
    std::cout << "Testing Supplier operations..." << std::endl;
    
    minimarket::products::Supplier supplier("SUP001", "TechCorp Inc.");
    
    assert(supplier.getSupplierId() == "SUP001");
    assert(supplier.getSupplierName() == "TechCorp Inc.");
    
    assert(supplier.addSuppliedProduct("PROD013") == true);
    assert(supplier.addSuppliedProduct("PROD014") == true);
    assert(supplier.addSuppliedProduct("") == false);
    
    assert(supplier.canSupplyProduct("PROD013") == true);
    assert(supplier.canSupplyProduct("PROD015") == false);
    
    assert(supplier.getSuppliedProductsCount() == 2);
    
    std::cout << "✅ testSupplierOperations: PASSED" << std::endl;
}

void testWarehouseManagement() {
    std::cout << "Testing Warehouse management..." << std::endl;
    
    minimarket::products::Warehouse warehouse("WH001", "Main Warehouse", 1000.0);
    
    assert(warehouse.getWarehouseId() == "WH001");
    assert(warehouse.getLocation() == "Main Warehouse");
    assert(warehouse.getCapacity() == 1000.0);
    
    assert(warehouse.allocateSpace(500.0) == true);
    assert(warehouse.allocateSpace(600.0) == false);
    
    double availableSpace = warehouse.calculateAvailableSpace();
    assert(availableSpace == 500.0);
    
    assert(warehouse.canStoreProduct(400.0) == true);
    assert(warehouse.canStoreProduct(600.0) == false);
    
    std::cout << "✅ testWarehouseManagement: PASSED" << std::endl;
}

void testBarcodeSystem() {
    std::cout << "Testing BarcodeSystem..." << std::endl;
    
    minimarket::products::BarcodeSystem barcodeSystem;
    
    assert(barcodeSystem.registerBarcode("PROD015", "123456789012") == true);
    assert(barcodeSystem.registerBarcode("PROD016", "invalid") == false);
    assert(barcodeSystem.registerBarcode("", "987654321098") == false);
    
    std::string productId = barcodeSystem.findProductByBarcode("123456789012");
    assert(productId == "PROD015");
    
    std::string notFound = barcodeSystem.findProductByBarcode("000000000000");
    assert(notFound.empty() == true);
    
    assert(barcodeSystem.validateBarcode("123456789012") == true);
    assert(barcodeSystem.validateBarcode("123") == false);
    assert(barcodeSystem.validateBarcode("12345678901A") == false);
    
    std::cout << "✅ testBarcodeSystem: PASSED" << std::endl;
}

void testProductReview() {
    std::cout << "Testing ProductReview..." << std::endl;
    
    minimarket::products::ProductReview review("REV001", "PROD017", 4, "Great product!");
    assert(review.getReviewId() == "REV001");
    assert(review.getProductId() == "PROD017");
    assert(review.getRating() == 4);
    assert(review.getComment() == "Great product!");
    
    assert(review.validateRating() == true);
    
    double impact = review.calculateReviewImpact();
    assert(impact == 0.8);
    
    std::string summary = review.generateSummary();
    assert(summary.find("4/5") != std::string::npos);
    assert(summary.find("Great product!") != std::string::npos);
    
    std::cout << "✅ testProductReview: PASSED" << std::endl;
}

void testReviewValidation() {
    std::cout << "Testing Review validation..." << std::endl;
    
    minimarket::products::ProductReview goodReview("REV002", "PROD018", 5, "Excellent");
    assert(goodReview.validateRating() == true);
    
    minimarket::products::ProductReview averageReview("REV003", "PROD019", 3, "Average");
    assert(averageReview.validateRating() == true);
    
    minimarket::products::ProductReview zeroReview("REV004", "PROD020", 0, "Bad");
    assert(zeroReview.validateRating() == false);
    
    minimarket::products::ProductReview highReview("REV005", "PROD021", 6, "Too high");
    assert(highReview.validateRating() == false);
    
    std::cout << "✅ testReviewValidation: PASSED" << std::endl;
}

void testProductSpecification() {
    std::cout << "Testing ProductSpecification..." << std::endl;
    
    minimarket::products::ProductSpecification spec("PROD022");
    
    assert(spec.addSpecification("Color", "Black") == true);
    assert(spec.addSpecification("Weight", "1.5kg") == true);
    assert(spec.addSpecification("", "Value") == false);
    assert(spec.addSpecification("Size", "") == false);
    
    assert(spec.getSpecification("Color") == "Black");
    assert(spec.getSpecification("Nonexistent").empty() == true);
    
    std::map<std::string, std::string> requirements = {{"Color", "Black"}, {"Weight", "1.5kg"}};
    assert(spec.meetsRequirements(requirements) == true);
    
    std::map<std::string, std::string> wrongRequirements = {{"Color", "White"}};
    assert(spec.meetsRequirements(wrongRequirements) == false);
    
    std::cout << "✅ testProductSpecification: PASSED" << std::endl;
}

void testProductIntegration() {
    std::cout << "Testing Product integration..." << std::endl;
    
    minimarket::products::Category electronics("CAT003", "Electronics");
    
    auto laptop = std::make_shared<minimarket::products::Product>("LAPTOP001", "Gaming Laptop", 1200.0);
    auto mouse = std::make_shared<minimarket::products::Product>("MOUSE001", "Gaming Mouse", 75.0);
    
    electronics.addProduct(laptop);
    electronics.addProduct(mouse);
    
    minimarket::products::Inventory inventory(2);
    inventory.updateStock("LAPTOP001", 5);
    inventory.updateStock("MOUSE001", 1);
    
    minimarket::products::DiscountSystem discounts;
    discounts.applyProductDiscount("MOUSE001", 10.0);
    
    assert(electronics.calculateCategoryRevenue() > 0.0);
    assert(inventory.getLowStockProducts().size() == 1);
    assert(discounts.isDiscountValid("MOUSE001") == true);
    
    std::cout << "✅ testProductIntegration: PASSED" << std::endl;
}

void testProductExceptions() {
    std::cout << "Testing Product exceptions..." << std::endl;
    
    try {
        minimarket::products::Product invalidProduct("PROD023", "Test", -50.0);
        assert(false);
    } catch (const minimarket::exceptions::InvalidOperationException&) {
    }
    
    std::cout << "✅ testProductExceptions: PASSED" << std::endl;
}

void testEmptyCategory() {
    std::cout << "Testing empty Category operations..." << std::endl;
    
    minimarket::products::Category emptyCategory("CAT004", "Empty Category");
    
    double revenue = emptyCategory.calculateCategoryRevenue();
    assert(revenue == 0.0);
    
    auto productNames = emptyCategory.getProductNames();
    assert(productNames.empty() == true);
    
    std::cout << "✅ testEmptyCategory: PASSED" << std::endl;
}

void runProductTests() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "RUNNING PRODUCT MANAGEMENT TESTS" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    testProductCreation();
    testProductDiscounts();
    testCategoryManagement();
    testCategoryRevenue();
    testInventoryManagement();
    testInventoryThreshold();
    testPricingStrategy();
    testDiscountSystem();
    testSupplierOperations();
    testWarehouseManagement();
    testBarcodeSystem();
    testProductReview();
    testReviewValidation();
    testProductSpecification();
    testProductIntegration();
    testProductExceptions();
    testEmptyCategory();
    
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "ALL PRODUCT TESTS PASSED! ✅" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}
