#include <iostream>
#include "../include/dictionary/Dictionary.hpp"
#include "../include/bigint/BigInt.hpp"

void displayMenu() {
    std::cout << "\n=== Main Menu ===\n";
    std::cout << "1. Test Dictionary\n";
    std::cout << "2. Test BigInt\n";
    std::cout << "3. Exit\n";
    std::cout << "Choice: ";
}

void testDictionary() {
    std::cout << "\n=== Dictionary Demo ===\n";
    
    dictionary::Dictionary dict;
    dict.addWord("hello", "привет");
    dict.addWord("world", "мир");
    dict.addWord("computer", "компьютер");
    
    std::cout << "Dictionary contents:\n";
    std::cout << dict;
    
    // Используем std::string чтобы избежать неоднозначности
    std::string hello = "hello";
    std::cout << "Translation of 'hello': " << dict[hello] << std::endl;
    std::cout << "Word count: " << dict.getWordCount() << std::endl;
}

void testBigInt() {
    std::cout << "\n=== BigInt Demo ===\n";
    
    bigint::BigInt a("123456789");
    bigint::BigInt b("987654321");
    
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "b - a = " << (b - a) << std::endl;
}

int main() {
    int choice;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                testDictionary();
                break;
            case 2:
                testBigInt();
                break;
            case 3:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
    
    return 0;
}
