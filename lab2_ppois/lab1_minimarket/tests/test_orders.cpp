#include "../include/orders/OrderSystem.hpp"
#include "../include/utils/Exceptions.hpp"
#include <iostream>
#include <cassert>
#include <memory>

void testOrderCreation() {
    std::cout << "Testing Order creation..." << std::endl;
    
    // Test valid order creation
    minimarket::orders::Order order("ORD001", "CUST001", 150.0);
    assert(order.getOrderId() == "ORD001");
    assert(order.validateOrder() == true);
    
    // Test order summary generation
    std::string summary = order.generateOrderSummary();
    assert(summary.find("ORD001") != std::string::npos);
    assert(summary.find("150.0") != std::string::npos);
    
    // Test tax calculation
    double tax = order.calculateTax();
    assert(tax == 12.0); // 8% of 150 = 12
    
    std::cout << "✅ testOrderCreation: PASSED" << std::endl;
}

void testOrderValidation() {
    std::cout << "Testing Order validation..." << std::endl;
    
    // Test valid order
    minimarket::orders::Order validOrder("ORD002", "CUST002", 75.50);
    assert(validOrder.validateOrder() == true);
    
    std::cout << "✅ testOrderValidation: PASSED" << std::endl;
}

void testOrderItemOperations() {
    std::cout << "Testing OrderItem operations..." << std::endl;
    
    // Test order item creation
    minimarket::orders::OrderItem item("PROD001", "Laptop", 1, 999.99);
    assert(item.getProductId() == "PROD001");
    assert(item.getProductName() == "Laptop");
    assert(item.getQuantity() == 1);
    assert(item.getUnitPrice() == 999.99);
    
    // Test item total calculation
    double itemTotal = item.calculateItemTotal();
    assert(itemTotal == 999.99);
    
    // Test quantity validation
    assert(item.validateQuantity() == true);
    
    // Test quantity discount
    minimarket::orders::OrderItem bulkItem("PROD002", "Mouse", 15, 25.0);
    bool discountApplied = bulkItem.applyQuantityDiscount();
    assert(discountApplied == true); // Should apply for 15 items
    
    std::cout << "✅ testOrderItemOperations: PASSED" << std::endl;
}

void testOrderItemValidation() {
    std::cout << "Testing OrderItem validation..." << std::endl;
    
    // Test valid quantities
    minimarket::orders::OrderItem validItem("PROD003", "Keyboard", 5, 45.0);
    assert(validItem.validateQuantity() == true);
    
    // Test invalid quantities
    try {
        minimarket::orders::OrderItem invalidItem("PROD004", "Monitor", 0, 200.0);
        assert(false); // Should not reach here
    } catch (const minimarket::exceptions::InvalidOperationException&) {
        // Expected - quantity must be positive
    }
    
    // Test maximum quantity
    minimarket::orders::OrderItem maxItem("PROD005", "Tablet", 100, 300.0);
    assert(maxItem.validateQuantity() == true);
    
    minimarket::orders::OrderItem overMaxItem("PROD006", "Phone", 101, 500.0);
    assert(overMaxItem.validateQuantity() == false);
    
    std::cout << "✅ testOrderItemValidation: PASSED" << std::endl;
}

void testPaymentProcessing() {
    std::cout << "Testing Payment processing..." << std::endl;
    
    // Test payment creation
    minimarket::orders::Payment payment("PAY001", "ORD001", 150.0, "CreditCard");
    assert(payment.getPaymentId() == "PAY001");
    assert(payment.getOrderId() == "ORD001");
    assert(payment.getAmount() == 150.0);
    assert(payment.getPaymentMethod() == "CreditCard");
    
    // Test payment processing
    bool processed = payment.processPayment();
    assert(processed == true); // Should succeed for valid amount
    
    // Test payment verification
    bool verified = payment.verifyPayment();
    assert(verified == true); // Should be verified after processing
    
    // Test payment confirmation
    std::string confirmation = payment.generatePaymentConfirmation();
    assert(confirmation.find("PAY001") != std::string::npos);
    assert(confirmation.find("150.0") != std::string::npos);
    
    std::cout << "✅ testPaymentProcessing: PASSED" << std::endl;
}

void testPaymentMethods() {
    std::cout << "Testing different Payment methods..." << std::endl;
    
    // Test Credit Card payment
    minimarket::orders::Payment ccPayment("PAY002", "ORD002", 2500.0, "CreditCard");
    assert(ccPayment.processPayment() == true); // Within $5000 limit
    
    // Test Bank Transfer payment
    minimarket::orders::Payment btPayment("PAY003", "ORD003", 8000.0, "BankTransfer");
    assert(btPayment.processPayment() == true); // Within $10000 limit
    
    // Test PayPal payment
    minimarket::orders::Payment ppPayment("PAY004", "ORD004", 2000.0, "PayPal");
    assert(ppPayment.processPayment() == true); // Within $2500 limit
    
    // Test failed payment (exceeds limits)
    minimarket::orders::Payment failedPayment("PAY005", "ORD005", 6000.0, "CreditCard");
    assert(failedPayment.processPayment() == false); // Exceeds $5000 limit
    
    std::cout << "✅ testPaymentMethods: PASSED" << std::endl;
}

void testShippingOperations() {
    std::cout << "Testing Shipping operations..." << std::endl;
    
    // Используем адрес с "Street" вместо "St"
    minimarket::orders::Shipping shipping("SHIP001", "ORD001", "123 Main Street, New York, 10001, USA", "Express");
    assert(shipping.getShippingId() == "SHIP001");
    assert(shipping.getOrderId() == "ORD001");
    
    // Test delivery scheduling
    bool scheduled = shipping.scheduleDelivery();
    assert(scheduled == true);
    
    // Test shipping days calculation
    int shippingDays = shipping.calculateShippingDays();
    assert(shippingDays >= 0);
    
    // Test address validation
    bool validAddress = shipping.validateShippingAddress();
    assert(validAddress == true);  // Теперь будет true
    
    std::cout << "✅ testShippingOperations: PASSED" << std::endl;
}

void testShippingMethods() {
    std::cout << "Testing different Shipping methods..." << std::endl;
    
    // Test Express shipping
    minimarket::orders::Shipping expressShipping("SHIP002", "ORD002", "456 Oak St, Chicago, 60007, USA", "Express");
    int expressDays = expressShipping.calculateShippingDays();
    assert(expressDays == 2); // Express should be 2 days
    
    // Test Standard shipping
    minimarket::orders::Shipping standardShipping("SHIP003", "ORD003", "789 Pine St, LA, 90001, USA", "Standard");
    int standardDays = standardShipping.calculateShippingDays();
    assert(standardDays == 5); // Standard should be 5 days
    
    std::cout << "✅ testShippingMethods: PASSED" << std::endl;
}

void testAddressValidation() {
    std::cout << "Testing address validation..." << std::endl;
    
    // Test valid address
    minimarket::orders::Shipping validShipping("SHIP004", "ORD004", "321 Elm Street, Boston, 02101, USA", "Standard");
    assert(validShipping.validateShippingAddress() == true);
    
    // Test invalid addresses
    minimarket::orders::Shipping shortAddress("SHIP005", "ORD005", "Short", "Express");
    assert(shortAddress.validateShippingAddress() == false);
    
    minimarket::orders::Shipping noStreet("SHIP006", "ORD006", "Boston, 02101, USA", "Standard");
    assert(noStreet.validateShippingAddress() == false);
    
    std::cout << "✅ testAddressValidation: PASSED" << std::endl;
}

void testShoppingCartOperations() {
    std::cout << "Testing ShoppingCart operations..." << std::endl;
    
    minimarket::orders::ShoppingCart cart("CART001", "CUST001");
    
    // Test cart creation
    assert(cart.getCartId() == "CART001");
    assert(cart.getCustomerId() == "CUST001");
    
    // Test adding items
    auto item1 = std::make_shared<minimarket::orders::OrderItem>("PROD001", "Laptop", 1, 999.99);
    auto item2 = std::make_shared<minimarket::orders::OrderItem>("PROD002", "Mouse", 2, 25.0);
    
    assert(cart.addItem(item1) == true);
    assert(cart.addItem(item2) == true);
    
    // Test cart total calculation
    double total = cart.calculateCartTotal();
    assert(total == 1049.99); // 999.99 + (2 * 25.0)
    
    // Test getting cart items
    auto items = cart.getCartItems();
    assert(items.size() == 2);
    assert(items[0].find("Laptop") != std::string::npos);
    assert(items[1].find("Mouse") != std::string::npos);
    
    std::cout << "✅ testShoppingCartOperations: PASSED" << std::endl;
}

void testShoppingCartItemManagement() {
    std::cout << "Testing ShoppingCart item management..." << std::endl;
    
    minimarket::orders::ShoppingCart cart("CART002", "CUST002");
    
    // Test adding duplicate items
    auto item1 = std::make_shared<minimarket::orders::OrderItem>("PROD003", "Keyboard", 1, 75.0);
    auto item1Duplicate = std::make_shared<minimarket::orders::OrderItem>("PROD003", "Keyboard", 1, 75.0);
    
    assert(cart.addItem(item1) == true);
    assert(cart.addItem(item1Duplicate) == false); // Should not allow duplicates
    
    // Test removing items
    auto item2 = std::make_shared<minimarket::orders::OrderItem>("PROD004", "Monitor", 1, 300.0);
    cart.addItem(item2);
    
    assert(cart.removeItem("PROD004") == true);
    assert(cart.removeItem("NONEXISTENT") == false);
    
    std::cout << "✅ testShoppingCartItemManagement: PASSED" << std::endl;
}

void testShoppingCartDiscounts() {
    std::cout << "Testing ShoppingCart discounts..." << std::endl;
    
    minimarket::orders::ShoppingCart cart("CART003", "CUST003");
    
    // Add items with quantity for discount testing
    auto bulkItem = std::make_shared<minimarket::orders::OrderItem>("PROD005", "USB Cable", 10, 5.0);
    cart.addItem(bulkItem);
    
    // Test applying valid discount
    bool discountApplied = cart.applyCartDiscount(10.0);
    assert(discountApplied == true);
    
    // Test applying invalid discount
    bool invalidDiscount = cart.applyCartDiscount(60.0); // Exceeds 50% max
    assert(invalidDiscount == false);
    
    bool negativeDiscount = cart.applyCartDiscount(-5.0);
    assert(negativeDiscount == false);
    
    std::cout << "✅ testShoppingCartDiscounts: PASSED" << std::endl;
}

void testOrderIntegration() {
    std::cout << "Testing Order integration..." << std::endl;
    
    // Create a complete order flow
    minimarket::orders::ShoppingCart cart("CART004", "CUST004");
    
    // Add items to cart
    auto item1 = std::make_shared<minimarket::orders::OrderItem>("PROD006", "Tablet", 1, 399.99);
    auto item2 = std::make_shared<minimarket::orders::OrderItem>("PROD007", "Case", 1, 19.99);
    cart.addItem(item1);
    cart.addItem(item2);
    
    // Calculate total
    double cartTotal = cart.calculateCartTotal();
    assert(cartTotal == 419.98);
    
    // Create order from cart total
    minimarket::orders::Order order("ORD006", "CUST004", cartTotal);
    assert(order.validateOrder() == true);
    
    // Process payment
    minimarket::orders::Payment payment("PAY006", "ORD006", cartTotal, "CreditCard");
    assert(payment.processPayment() == true);
    
    // Schedule shipping
    minimarket::orders::Shipping shipping("SHIP007", "ORD006", "123 Commerce St, Seattle, 98101, USA", "Express");
    assert(shipping.scheduleDelivery() == true);
    
    std::cout << "✅ testOrderIntegration: PASSED" << std::endl;
}

void testOrderExceptions() {
    std::cout << "Testing Order exceptions..." << std::endl;
    
    // Test invalid order amount
    try {
        minimarket::orders::Order invalidOrder("ORD007", "CUST005", -50.0);
        assert(false); // Should not reach here
    } catch (const minimarket::exceptions::InvalidOperationException&) {
        // Expected
    }
    
    // Test invalid order item quantity
    try {
        minimarket::orders::OrderItem invalidItem("PROD008", "Charger", 0, 15.0);
        assert(false); // Should not reach here
    } catch (const minimarket::exceptions::InvalidOperationException&) {
        // Expected
    }
    
    std::cout << "✅ testOrderExceptions: PASSED" << std::endl;
}

void testEmptyCartOperations() {
    std::cout << "Testing empty ShoppingCart operations..." << std::endl;
    
    minimarket::orders::ShoppingCart emptyCart("CART005", "CUST005");
    
    // Test total calculation on empty cart
    double total = emptyCart.calculateCartTotal();
    assert(total == 0.0);
    
    // Test getting items from empty cart
    auto items = emptyCart.getCartItems();
    assert(items.empty() == true);
    
    // Test removing from empty cart
    bool removed = emptyCart.removeItem("ANYPRODUCT");
    assert(removed == false);
    
    // Test discount application on empty cart
    bool discountApplied = emptyCart.applyCartDiscount(10.0);
    assert(discountApplied == true); // Should still return true
    
    std::cout << "✅ testEmptyCartOperations: PASSED" << std::endl;
}

void runOrderTests() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "RUNNING ORDER SYSTEM TESTS" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    testOrderCreation();
    testOrderValidation();
    testOrderItemOperations();
    testOrderItemValidation();
    testPaymentProcessing();
    testPaymentMethods();
    testShippingOperations();
    testShippingMethods();
    testAddressValidation();
    testShoppingCartOperations();
    testShoppingCartItemManagement();
    testShoppingCartDiscounts();
    testOrderIntegration();
    testOrderExceptions();
    testEmptyCartOperations();
    
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "ALL ORDER TESTS PASSED! ✅" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}
