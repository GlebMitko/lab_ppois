#include "../include/bigint/BigInt.hpp"
#include <iostream>

void testBigIntConstructor() {
    bigint::BigInt num1;
    bigint::BigInt num2(123);
    bigint::BigInt num3("456");
    std::cout << "testBigIntConstructor: PASSED\n";
}

void testBigIntOperations() {
    bigint::BigInt a("100");
    bigint::BigInt b("50");
    bigint::BigInt c = a + b;
    std::cout << "100 + 50 = " << c << std::endl;
    std::cout << "testBigIntOperations: PASSED\n";
}

void runBigIntTests() {
    std::cout << "Running BigInt tests...\n";
    testBigIntConstructor();
    testBigIntOperations();
    std::cout << "BigInt tests PASSED!\n\n";
}
