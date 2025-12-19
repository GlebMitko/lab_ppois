// src/main.cpp

#include <iostream>
#include <memory>
#include <string>

// === Banking System ===
#include "../include/banking/Bank.hpp"
#include "../include/banking/Account.hpp"
#include "../include/banking/Card.hpp"
#include "../include/banking/CreditCard.hpp"
#include "../include/banking/Transaction.hpp"

// === Product Management ===
#include "../include/products/Product.hpp"
#include "../include/products/Category.hpp"
#include "../include/products/Inventory.hpp"
#include "../include/products/DiscountSystem.hpp"

// === User System ===
#include "../include/users/Customer.hpp"
#include "../include/users/Employee.hpp"
#include "../include/users/Admin.hpp"
#include "../include/users/UserProfile.hpp"
#include "../include/users/Address.hpp"

// === Order System ===
#include "../include/orders/Order.hpp"
#include "../include/orders/OrderItem.hpp"
#include "../include/orders/ShoppingCart.hpp"
#include "../include/orders/Payment.hpp"

// === Utils ===
#include "../include/utils/Exceptions.hpp"

using namespace minimarket;

void displayMenu() {
    std::cout << "\n=== Minimarket System Menu ===" << std::endl;
    std::cout << "1. Test Banking System" << std::endl;
    std::cout << "2. Test Product Management" << std::endl;
    std::cout << "3. Test User System" << std::endl;
    std::cout << "4. Test Order System" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Choice: ";
}

void testBankingSystem() {
    std::cout << "\n=== Banking System Demo ===" << std::endl;
    
    try {
        banking::Bank bank("BANK001", "Minimarket Bank");
        std::cout << "Bank created: " << bank.getBankName() << std::endl;
        
        auto account1 = std::make_shared<banking::Account>("ACC001", "John Doe");
        auto account2 = std::make_shared<banking::Account>("ACC002", "Jane Smith");
        
        bank.addAccount(account1);
        bank.addAccount(account2);
        
        banking::Card card("1234567812345678", "John Doe", "12/25");
        std::cout << "Card created: " << card.getCardNumber() << std::endl;
        
        if (card.verifyPin("1234")) {
            std::cout << "PIN verification: SUCCESS" << std::endl;
        } else {
            std::cout << "PIN verification: FAILED" << std::endl;
        }
        
        // CreditCard: убран 5-й параметр (APR)
        banking::CreditCard creditCard("8765432187654321", "John Doe", "06/26", 5000.0);
        std::cout << "Credit card limit: $" << creditCard.getCreditLimit() << std::endl;
        
        banking::Transaction transaction("TXN001", 100.0, "Payment");
        std::cout << "Transaction receipt: " << transaction.generateReceipt() << std::endl;
        
        std::cout << "Bank accounts count: " << bank.getTotalAccountsCount() << std::endl;
        std::cout << "Banking demo completed successfully!" << std::endl;
        
    } catch (const exceptions::InsufficientFundsException& e) {
        std::cout << "Banking error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void testProductManagement() {
    std::cout << "\n=== Product Management Demo ===" << std::endl;
    
    try {
        products::Product product1("PROD001", "Laptop", 999.99);
        products::Product product2("PROD002", "Mouse", 29.99);
        
        std::cout << "Product 1: " << product1.getProductInfo() << std::endl;
        std::cout << "Product 2: " << product2.getProductInfo() << std::endl;
        
        products::Category category("CAT001", "Electronics");
        category.addProduct(std::make_shared<products::Product>(product1));
        category.addProduct(std::make_shared<products::Product>(product2));
        
        std::cout << "Category revenue: $" << category.calculateCategoryRevenue() << std::endl;
        
        products::Inventory inventory(5);
        inventory.updateStock("PROD001", 10);
        inventory.updateStock("PROD002", 3);
        
        auto lowStock = inventory.getLowStockProducts();
        if (!lowStock.empty()) {
            std::cout << "Low stock products: ";
            for (const auto& product : lowStock) {
                std::cout << product << " ";
            }
            std::cout << std::endl;
        }
        
        products::DiscountSystem discounts;
        discounts.applyProductDiscount("PROD001", 10.0);
        std::cout << "Loyalty discount on $100: $" << discounts.calculateLoyaltyDiscount(100.0) << std::endl;
        
        std::cout << "Product management demo completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void testUserSystem() {
    std::cout << "\n=== User System Demo ===" << std::endl;
    
    try {
        users::Customer customer("CUST001", "John Customer", "john@email.com", "+1234567890");
        users::Employee employee("EMP001", "Jane Employee", "jane@bank.com", "Loans", 50000.0);
        users::Admin admin("ADM001", "Admin User", "admin@system.com", "SuperAdmin");
        
        std::cout << "Customer: " << customer.getUserRole() << std::endl;
        std::cout << "Employee: " << employee.getUserRole() << std::endl;
        std::cout << "Admin: " << admin.getUserRole() << std::endl;
        
        if (customer.authenticate("Password123!")) {
            std::cout << "Customer authentication: SUCCESS" << std::endl;
        } else {
            std::cout << "Customer authentication: FAILED" << std::endl;
        }
        
        users::UserProfile profile("CUST001", "John", "Doe", "15/05/1990");
        std::cout << "Full name: " << profile.getFullName() << std::endl;
        std::cout << "Age: " << profile.calculateAge() << std::endl;
        std::cout << "Is adult: " << (profile.isAdult() ? "Yes" : "No") << std::endl;
        
        users::Address address("123 Main St", "New York", "10001", "USA");
        std::cout << "Formatted address: " << address.getFormattedAddress() << std::endl;
        std::cout << "Address valid: " << (address.validateAddress() ? "Yes" : "No") << std::endl;
        
        std::cout << "User system demo completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void testOrderSystem() {
    std::cout << "\n=== Order System Demo ===" << std::endl;
    
    try {
        orders::Order order("ORD001", "CUST001", 150.0);
        std::cout << "Order summary: " << order.generateOrderSummary() << std::endl;
        std::cout << "Order valid: " << (order.validateOrder() ? "Yes" : "No") << std::endl;
        
        auto item1 = std::make_shared<orders::OrderItem>("PROD001", "Laptop", 1, 999.99);
        auto item2 = std::make_shared<orders::OrderItem>("PROD002", "Mouse", 2, 29.99);
        
        std::cout << "Item 1 total: $" << item1->calculateItemTotal() << std::endl;
        std::cout << "Item 2 total: $" << item2->calculateItemTotal() << std::endl;
        
        orders::ShoppingCart cart("CART001", "CUST001");
        cart.addItem(item1);
        cart.addItem(item2);
        
        std::cout << "Cart total: $" << cart.calculateCartTotal() << std::endl;
        
        auto cartItems = cart.getCartItems();
        std::cout << "Cart items: ";
        for (const auto& item : cartItems) {
            std::cout << item << ", ";
        }
        std::cout << std::endl;
        
        orders::Payment payment("PAY001", "ORD001", 150.0, "CreditCard");
        if (payment.processPayment()) {
            std::cout << "Payment processed: SUCCESS" << std::endl;
            std::cout << "Payment confirmation: " << payment.generatePaymentConfirmation() << std::endl;
        } else {
            std::cout << "Payment processed: FAILED" << std::endl;
        }
        
        std::cout << "Order system demo completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

int main() {
    int choice;
    
    std::cout << "=== Minimarket Management System ===" << std::endl;
    std::cout << "50 Classes | 130+ Behaviors | 150+ Fields" << std::endl;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                testBankingSystem();
                break;
            case 2:
                testProductManagement();
                break;
            case 3:
                testUserSystem();
                break;
            case 4:
                testOrderSystem();
                break;
            case 5:
                std::cout << "Thank you for using Minimarket System! Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);
    
    return 0;
}
