#include "../include/utils/StringUtils.hpp"
#include <iostream>
#include <cassert>

void testToLower() {
    assert(utils::StringUtils::toLower("HELLO") == "hello");
    assert(utils::StringUtils::toLower("Hello World") == "hello world");
    assert(utils::StringUtils::toLower("123ABC") == "123abc");
    assert(utils::StringUtils::toLower("") == "");
    assert(utils::StringUtils::toLower("already lowercase") == "already lowercase");
    std::cout << "✅ testToLower: PASSED\n";
}

void testTrim() {
    assert(utils::StringUtils::trim("  hello  ") == "hello");
    assert(utils::StringUtils::trim("  hello world  ") == "hello world");
    assert(utils::StringUtils::trim("hello") == "hello");
    assert(utils::StringUtils::trim("   ") == "");
    assert(utils::StringUtils::trim("") == "");
    assert(utils::StringUtils::trim("\t\nhello\t\n") == "hello");
    std::cout << "✅ testTrim: PASSED\n";
}

void testIsNumber() {
    assert(utils::StringUtils::isNumber("12345"));
    assert(utils::StringUtils::isNumber("0"));
    assert(utils::StringUtils::isNumber("-123"));
    assert(utils::StringUtils::isNumber("+456"));
    
    assert(!utils::StringUtils::isNumber(""));
    assert(!utils::StringUtils::isNumber("12a34"));
    assert(!utils::StringUtils::isNumber("abc"));
    assert(!utils::StringUtils::isNumber("12.34"));
    assert(!utils::StringUtils::isNumber("--123"));
    assert(!utils::StringUtils::isNumber("++456"));
    
    std::cout << "✅ testIsNumber: PASSED\n";
}

void testCombinedOperations() {
    std::string test1 = "  HELLO World  ";
    std::string result1 = utils::StringUtils::trim(utils::StringUtils::toLower(test1));
    assert(result1 == "hello world");
    
    std::string test2 = "  -123  ";
    std::string trimmed = utils::StringUtils::trim(test2);
    assert(utils::StringUtils::isNumber(trimmed));
    
    std::cout << "✅ testCombinedOperations: PASSED\n";
}

void runStringUtilsTests() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "RUNNING STRING UTILS TESTS\n";
    std::cout << std::string(50, '=') << "\n";
    
    testToLower();
    testTrim();
    testIsNumber();
    testCombinedOperations();
    
    std::cout << std::string(50, '=') << "\n";
    std::cout << "ALL STRING UTILS TESTS PASSED! ✅\n";
    std::cout << std::string(50, '=') << "\n\n";
}
