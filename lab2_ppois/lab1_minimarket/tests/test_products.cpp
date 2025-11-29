#include "../include/products/ProductManagement.hpp"
#include "../include/utils/Exceptions.hpp"
#include <iostream>
#include <cassert>
#include <memory>

void testProductCreation() {
    std::cout << "Testing Product creation..." << std::endl;
    
    // Test valid product creation
    minimarket::products::Product product("PROD001", "Laptop", 999.99);
    assert(product.getProductId() == "PROD001");
    assert(product.getProductName() == "Laptop");
    assert(product.getBasePrice() == 999.99);
    
    // Test final price calculation
    double finalPrice = product.calculateFinalPrice();
    assert(finalPrice == 1199.988); // 999.99 * 1.2 (20% tax)
    
    // Test product info generation
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
    
    // Test valid discount application
    bool discountApplied = product.applyDiscount(10.0); // 10% discount
    assert(discountApplied == true);
    assert(product.getBasePrice() == 45.0); // 50 - 10%
    
    // Test invalid discounts
    bool negativeDiscount = product.applyDiscount(-5.0);
    assert(negativeDiscount == false);
    
    bool excessiveDiscount = product.applyDiscount(110.0); // More than 100%
    assert(excessiveDiscount == false);
    
    std::cout << "✅ testProductDiscounts: PASSED" << std::endl;
}

void testCategoryManagement() {
    std::cout << "Testing Category management..." << std::endl;
    
    minimarket::products::Category category("CAT001", "Electronics");
    
    // Test category creation
    assert(category.getCategoryId() == "CAT001");
    assert(category.getCategoryName() == "Electronics");
    
    // Test adding products to category
    auto product1 = std::make_shared<minimarket::products::Product>("PROD003", "Tablet", 299.99);
    auto product2 = std::make_shared<minimarket::products::Product>("PROD004", "Phone", 599.99);
    
    assert(category.addProduct(product1) == true);
    assert(category.addProduct(product2) == true);
    
    // Test revenue calculation
    double revenue = category.calculateCategoryRevenue();
    assert(revenue > 0.0);
    
    // Test getting product names
    auto productNames = category.getProductNames();
    assert(productNames.size() == 2);
    
    std::cout << "✅ testCategoryManagement: PASSED" << std::endl;
}

void testCategoryRevenue() {
    std::cout << "Testing Category revenue calculation..." << std::endl;
    
    minimarket::products::Category category("CAT002", "Books");
    
    // Add products with known prices
    auto book1 = std::make_shared<minimarket::products::Product>("BOOK001", "Novel", 20.0);
    auto book2 = std::make_shared<minimarket::products::Product>("BOOK002", "Textbook", 80.0);
    
    category.addProduct(book1);
    category.addProduct(book2);
    
    // Calculate expected revenue (20 + 80) * 1.2 = 120
    double revenue = category.calculateCategoryRevenue();
    assert(revenue == 120.0);
    
    std::cout << "✅ testCategoryRevenue: PASSED" << std::endl;
}

void testInventoryManagement() {
    std::cout << "Testing Inventory management..." << std::endl;
    
    minimarket::products::Inventory inventory(5); // Low stock threshold = 5
    
    // Test stock updates
    assert(inventory.updateStock("PROD005", 10) == true);
    assert(inventory.updateStock("PROD006", 3) == true);
    
    // Test availability checks
    assert(inventory.checkAvailability("PROD005", 5) == true);
    assert(inventory.checkAvailability("PROD005", 15) == false); // Not enough stock
    assert(inventory.checkAvailability("NONEXISTENT", 1) == false);
    
    // Test low stock detection
    auto lowStock = inventory.getLowStockProducts();
    assert(lowStock.size() == 1);
    assert(lowStock[0] == "PROD006"); // Only 3 in stock
    
    std::cout << "✅ testInventoryManagement: PASSED" << std::endl;
}

void testInventoryThreshold() {
    std::cout << "Testing Inventory threshold..." << std::endl;
    
    minimarket::products::Inventory inventory(3); // Low threshold = 3
    
    // Add products with various stock levels
    inventory.updateStock("PROD007", 10); // Above threshold
    inventory.updateStock("PROD008", 3);  // At threshold (считается low stock)
    inventory.updateStock("PROD009", 2);  // Below threshold
    inventory.updateStock("PROD010", 0);  // Zero stock
    
    auto lowStock = inventory.getLowStockProducts();
    
    // Debug output
    std::cout << "Low stock products count: " << lowStock.size() << std::endl;
    for (const auto& product : lowStock) {
        std::cout << "Low stock: " << product << std::endl;
    }
    
    // Ожидаем 3 продукта: PROD008 (на пороге), PROD009 и PROD010 (ниже порога)
    assert(lowStock.size() == 3);
    assert(std::find(lowStock.begin(), lowStock.end(), "PROD008") != lowStock.end());
    assert(std::find(lowStock.begin(), lowStock.end(), "PROD009") != lowStock.end());
    assert(std::find(lowStock.begin(), lowStock.end(), "PROD010") != lowStock.end());
    
    std::cout << "✅ testInventoryThreshold: PASSED" << std::endl;
}

void testPricingStrategy() {
    std::cout << "Testing PricingStrategy..." << std::endl;
    
    minimarket::products::PricingStrategy strategy("Premium", 25.0); // 25% markup
    
    // Test price application
    double sellingPrice = strategy.applyPricing(100.0);
    assert(sellingPrice == 125.0); // 100 + 25%
    
    // Test price validation
    assert(strategy.validatePricing(100.0, 125.0) == true); // Valid markup
    assert(strategy.validatePricing(100.0, 50.0) == false); // Below cost
    assert(strategy.validatePricing(100.0, 400.0) == false); // Exceeds 300% max
    
    std::cout << "✅ testPricingStrategy: PASSED" << std::endl;
}

void testDiscountSystem() {
    std::cout << "Testing DiscountSystem..." << std::endl;
    
    minimarket::products::DiscountSystem discounts(5.0); // 5% loyalty discount
    
    // Test product discount application
    assert(discounts.applyProductDiscount("PROD011", 15.0) == true);
    assert(discounts.applyProductDiscount("PROD012", 60.0) == false); // Exceeds 50% max
    
    // Test loyalty discount calculation
    double loyaltyDiscount = discounts.calculateLoyaltyDiscount(200.0);
    assert(loyaltyDiscount == 10.0); // 5% of 200
    
    // Test discount validation
    assert(discounts.isDiscountValid("PROD011") == true);
    assert(discounts.isDiscountValid("NONEXISTENT") == false);
    
    std::cout << "✅ testDiscountSystem: PASSED" << std::endl;
}

void testSupplierOperations() {
    std::cout << "Testing Supplier operations..." << std::endl;
    
    minimarket::products::Supplier supplier("SUP001", "TechCorp Inc.");
    
    // Test supplier creation
    assert(supplier.getSupplierId() == "SUP001");
    assert(supplier.getSupplierName() == "TechCorp Inc.");
    
    // Test adding supplied products
    assert(supplier.addSuppliedProduct("PROD013") == true);
    assert(supplier.addSuppliedProduct("PROD014") == true);
    assert(supplier.addSuppliedProduct("") == false); // Invalid product ID
    
    // Test product supply capability
    assert(supplier.canSupplyProduct("PROD013") == true);
    assert(supplier.canSupplyProduct("PROD015") == false); // Not supplied
    
    // Test product count
    assert(supplier.getSuppliedProductsCount() == 2);
    
    std::cout << "✅ testSupplierOperations: PASSED" << std::endl;
}

void testWarehouseManagement() {
    std::cout << "Testing Warehouse management..." << std::endl;
    
    minimarket::products::Warehouse warehouse("WH001", "Main Warehouse", 1000.0);
    
    // Test warehouse creation
    assert(warehouse.getWarehouseId() == "WH001");
    assert(warehouse.getLocation() == "Main Warehouse");
    assert(warehouse.getCapacity() == 1000.0);
    
    // Test space allocation
    assert(warehouse.allocateSpace(500.0) == true);
    assert(warehouse.allocateSpace(600.0) == false); // Exceeds capacity
    
    // Test available space calculation
    double availableSpace = warehouse.calculateAvailableSpace();
    assert(availableSpace == 500.0); // 1000 - 500
    
    // Test product storage capability
    assert(warehouse.canStoreProduct(400.0) == true);
    assert(warehouse.canStoreProduct(600.0) == false);
    
    std::cout << "✅ testWarehouseManagement: PASSED" << std::endl;
}

void testBarcodeSystem() {
    std::cout << "Testing BarcodeSystem..." << std::endl;
    
    minimarket::products::BarcodeSystem barcodeSystem;
    
    // Test barcode registration
    assert(barcodeSystem.registerBarcode("PROD015", "123456789012") == true);
    assert(barcodeSystem.registerBarcode("PROD016", "invalid") == false); // Wrong length
    assert(barcodeSystem.registerBarcode("", "987654321098") == false); // Empty product ID
    
    // Test product lookup
    std::string productId = barcodeSystem.findProductByBarcode("123456789012");
    assert(productId == "PROD015");
    
    std::string notFound = barcodeSystem.findProductByBarcode("000000000000");
    assert(notFound.empty() == true);
    
    // Test barcode validation
    assert(barcodeSystem.validateBarcode("123456789012") == true);
    assert(barcodeSystem.validateBarcode("123") == false); // Too short
    assert(barcodeSystem.validateBarcode("12345678901A") == false); // Non-digit
    
    std::cout << "✅ testBarcodeSystem: PASSED" << std::endl;
}

void testProductReview() {
    std::cout << "Testing ProductReview..." << std::endl;
    
    // Test valid review creation
    minimarket::products::ProductReview review("REV001", "PROD017", 4, "Great product!");
    assert(review.getReviewId() == "REV001");
    assert(review.getProductId() == "PROD017");
    assert(review.getRating() == 4);
    assert(review.getComment() == "Great product!");
    
    // Test rating validation
    assert(review.validateRating() == true);
    
    // Test review impact calculation
    double impact = review.calculateReviewImpact();
    assert(impact == 0.8); // 4 * 0.2
    
    // Test review summary generation
    std::string summary = review.generateSummary();
    assert(summary.find("4/5") != std::string::npos);
    assert(summary.find("Great product!") != std::string::npos);
    
    std::cout << "✅ testProductReview: PASSED" << std::endl;
}

void testReviewValidation() {
    std::cout << "Testing Review validation..." << std::endl;
    
    // Test valid ratings
    minimarket::products::ProductReview goodReview("REV002", "PROD018", 5, "Excellent");
    assert(goodReview.validateRating() == true);
    
    minimarket::products::ProductReview averageReview("REV003", "PROD019", 3, "Average");
    assert(averageReview.validateRating() == true);
    
    // Test invalid ratings
    minimarket::products::ProductReview zeroReview("REV004", "PROD020", 0, "Bad");
    assert(zeroReview.validateRating() == false);
    
    minimarket::products::ProductReview highReview("REV005", "PROD021", 6, "Too high");
    assert(highReview.validateRating() == false);
    
    std::cout << "✅ testReviewValidation: PASSED" << std::endl;
}

void testProductSpecification() {
    std::cout << "Testing ProductSpecification..." << std::endl;
    
    minimarket::products::ProductSpecification spec("PROD022");
    
    // Test adding specifications
    assert(spec.addSpecification("Color", "Black") == true);
    assert(spec.addSpecification("Weight", "1.5kg") == true);
    assert(spec.addSpecification("", "Value") == false); // Empty key
    assert(spec.addSpecification("Size", "") == false); // Empty value
    
    // Test getting specifications
    assert(spec.getSpecification("Color") == "Black");
    assert(spec.getSpecification("Nonexistent").empty() == true);
    
    // Test requirements matching
    std::map<std::string, std::string> requirements = {{"Color", "Black"}, {"Weight", "1.5kg"}};
    assert(spec.meetsRequirements(requirements) == true);
    
    std::map<std::string, std::string> wrongRequirements = {{"Color", "White"}};
    assert(spec.meetsRequirements(wrongRequirements) == false);
    
    std::cout << "✅ testProductSpecification: PASSED" << std::endl;
}

void testProductIntegration() {
    std::cout << "Testing Product integration..." << std::endl;
    
    // Create a complete product workflow
    minimarket::products::Category electronics("CAT003", "Electronics");
    
    // Create products
    auto laptop = std::make_shared<minimarket::products::Product>("LAPTOP001", "Gaming Laptop", 1200.0);
    auto mouse = std::make_shared<minimarket::products::Product>("MOUSE001", "Gaming Mouse", 75.0);
    
    // Add to category
    electronics.addProduct(laptop);
    electronics.addProduct(mouse);
    
    // Set up inventory
    minimarket::products::Inventory inventory(2);
    inventory.updateStock("LAPTOP001", 5);
    inventory.updateStock("MOUSE001", 1); // Low stock
    
    // Set up discounts
    minimarket::products::DiscountSystem discounts;
    discounts.applyProductDiscount("MOUSE001", 10.0);
    
    // Verify the integration
    assert(electronics.calculateCategoryRevenue() > 0.0);
    assert(inventory.getLowStockProducts().size() == 1);
    assert(discounts.isDiscountValid("MOUSE001") == true);
    
    std::cout << "✅ testProductIntegration: PASSED" << std::endl;
}

void testProductExceptions() {
    std::cout << "Testing Product exceptions..." << std::endl;
    
    // Test invalid product price
    try {
        minimarket::products::Product invalidProduct("PROD023", "Test", -50.0);
        assert(false); // Should not reach here
    } catch (const minimarket::exceptions::InvalidOperationException&) {
        // Expected
    }
    
    std::cout << "✅ testProductExceptions: PASSED" << std::endl;
}

void testEmptyCategory() {
    std::cout << "Testing empty Category operations..." << std::endl;
    
    minimarket::products::Category emptyCategory("CAT004", "Empty Category");
    
    // Test revenue calculation on empty category
    double revenue = emptyCategory.calculateCategoryRevenue();
    assert(revenue == 0.0);
    
    // Test product names on empty category
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
