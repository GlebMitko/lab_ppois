#include "../include/bigint/BigInt.hpp"
#include <iostream>
#include <cassert>
#include <climits>
#include <sstream>
#include <string>

void testBigIntDefaultConstructor() {
    bigint::BigInt num;
    assert(num.toString() == "0");
    assert(num.isZero());
    std::cout << "✅ testBigIntDefaultConstructor: PASSED\n";
}

void testBigIntIntConstructor() {
    bigint::BigInt num1(12345);
    assert(num1.toString() == "12345");
    
    bigint::BigInt num2(-6789);
    assert(num2.toString() == "-6789");
    
    bigint::BigInt num3(0);
    assert(num3.toString() == "0");
    
    std::cout << "✅ testBigIntIntConstructor: PASSED\n";
}

void testBigIntStringConstructor() {
    bigint::BigInt num1("123456789");
    assert(num1.toString() == "123456789");
    
    bigint::BigInt num2("-987654321");
    assert(num2.toString() == "-987654321");
    
    bigint::BigInt num3("0");
    assert(num3.toString() == "0");
    
    std::cout << "✅ testBigIntStringConstructor: PASSED\n";
}

void testBigIntCharPtrConstructor() {
    bigint::BigInt num1("999999");
    assert(num1.toString() == "999999");
    
    std::cout << "✅ testBigIntCharPtrConstructor: PASSED\n";
}

void testBigIntAddition() {
    bigint::BigInt a("123");
    bigint::BigInt b("456");
    bigint::BigInt c = a + b;
    assert(c.toString() == "579");
    

    bigint::BigInt d("-100");
    bigint::BigInt e("50");
    bigint::BigInt f = d + e;
    assert(f.toString() == "-50");
    
    std::cout << "✅ testBigIntAddition: PASSED\n";
}

void testBigIntSubtraction() {
    bigint::BigInt a("1000");
    bigint::BigInt b("500");
    bigint::BigInt c = a - b;
    assert(c.toString() == "500");
    
    bigint::BigInt d("100");
    bigint::BigInt e("200");
    bigint::BigInt f = d - e;
    assert(f.toString() == "-100");
    
    std::cout << "✅ testBigIntSubtraction: PASSED\n";
}

void testBigIntMultiplication() {
    bigint::BigInt a("123");
    bigint::BigInt b("456");
    bigint::BigInt c = a * b;
    assert(c.toString() == "56088");
    
    bigint::BigInt d("-10");
    bigint::BigInt e("5");
    bigint::BigInt f = d * e;
    assert(f.toString() == "-50");
    
    std::cout << "✅ testBigIntMultiplication: PASSED\n";
}

void testBigIntDivision() {
    bigint::BigInt a("1000");
    bigint::BigInt b("25");
    bigint::BigInt c = a / b;
    assert(c.toString() == "40");
    
    bigint::BigInt d("100");
    bigint::BigInt e("3");
    bigint::BigInt f = d / e;
    assert(f.toString() == "33");
    
    std::cout << "✅ testBigIntDivision: PASSED\n";
}

void testBigIntAssignmentOperators() {
    bigint::BigInt a("100");
    bigint::BigInt b("50");
    
    a += b;
    assert(a.toString() == "150");
    
    a -= b;
    assert(a.toString() == "100");
    
    a *= bigint::BigInt("2");
    assert(a.toString() == "200");
    
    a /= bigint::BigInt("4");
    assert(a.toString() == "50");
    
    std::cout << "✅ testBigIntAssignmentOperators: PASSED\n";
}

void testBigIntIncrementDecrement() {
    bigint::BigInt a("10");
    
    ++a;
    assert(a.toString() == "11");
    
    a++;
    assert(a.toString() == "12");
    
    --a;
    assert(a.toString() == "11");
    
    a--;
    assert(a.toString() == "10");
    
    std::cout << "✅ testBigIntIncrementDecrement: PASSED\n";
}

void testBigIntComparison() {
    bigint::BigInt a("100");
    bigint::BigInt b("200");
    bigint::BigInt c("100");
    
    assert(a == c);
    assert(a != b);
    assert(a < b);
    assert(b > a);
    assert(a <= c);
    assert(b >= a);
    
    std::cout << "✅ testBigIntComparison: PASSED\n";
}

void testBigIntUnaryOperators() {
    bigint::BigInt a("123");
    bigint::BigInt b = -a;
    bigint::BigInt c = +a;
    
    assert(b.toString() == "-123");
    assert(c.toString() == "123");
    
    std::cout << "✅ testBigIntUnaryOperators: PASSED\n";
}

void testBigIntIntConversion() {
    bigint::BigInt a(12345);

    if (a < bigint::BigInt(INT_MAX) && a > bigint::BigInt(INT_MIN)) {
        int b = static_cast<int>(a);
        assert(b == 12345);
    }
    
    std::cout << "✅ testBigIntIntConversion: PASSED\n";
}

void testBigIntLargeNumbers() {
    bigint::BigInt a("12345678901234567890");
    bigint::BigInt b("98765432109876543210");
    
    bigint::BigInt c = a + b;
    assert(c.toString() == "111111111011111111100");
    
    std::cout << "✅ testBigIntLargeNumbers: PASSED\n";
}

void testBigIntZeroOperations() {
    bigint::BigInt zero(0);
    bigint::BigInt num("123");
    
    assert(zero.isZero());
    assert(!num.isZero());
    
    assert((zero + num).toString() == "123");
    assert((num + zero).toString() == "123");
    assert((zero * num).toString() == "0");
    
    std::cout << "✅ testBigIntZeroOperations: PASSED\n";
}

void testBigIntWithIntOperations() {
    bigint::BigInt a("1000");
    
    bigint::BigInt b = a + 500;
    assert(b.toString() == "1500");
    
    bigint::BigInt c = a - 500;
    assert(c.toString() == "500");
    
    bigint::BigInt d = a * 2;
    assert(d.toString() == "2000");
    
    bigint::BigInt e = a / 4;
    assert(e.toString() == "250");
    
    std::cout << "✅ testBigIntWithIntOperations: PASSED\n";
}

void testBigIntStreamOperators() {
    bigint::BigInt num("123456");
    

    std::ostringstream oss;
    oss << num;
    assert(oss.str() == "123456");
    
    std::cout << "✅ testBigIntStreamOperators: PASSED\n";
}


void testBigIntEdgeCases() {

    bigint::BigInt maxInt(INT_MAX);
    bigint::BigInt minInt(INT_MIN);
    
    assert(maxInt.toString() == std::to_string(INT_MAX));
    assert(minInt.toString() == std::to_string(INT_MIN));
    
    std::cout << "✅ testBigIntEdgeCases: PASSED\n";
}

void testBigIntInvalidString() {

    try {
        bigint::BigInt num("123abc");
        assert(false && "Should have thrown exception");
    } catch (const std::invalid_argument&) {
    }
    
    try {
        bigint::BigInt num("12.34");
        assert(false && "Should have thrown exception");
    } catch (const std::invalid_argument&) {
    }
    
    std::cout << "✅ testBigIntInvalidString: PASSED\n";
}

void testBigIntDivisionByZero() {
    bigint::BigInt a("100");
    bigint::BigInt zero(0);
    

    try {
        bigint::BigInt result = a / zero;
        assert(false && "Should have thrown exception");
    } catch (const std::runtime_error&) {
    }
    

    try {
        a /= zero;
        assert(false && "Should have thrown exception");
    } catch (const std::runtime_error&) {
    }
    
    std::cout << "✅ testBigIntDivisionByZero: PASSED\n";
}

void testBigIntOverflowConversion() {

    bigint::BigInt tooLarge("999999999999999999999999");
    bigint::BigInt tooSmall("-999999999999999999999999");
    
    try {
        int result = static_cast<int>(tooLarge);
        assert(false && "Should have thrown overflow_error");
    } catch (const std::overflow_error&) {
    }
    
    try {
        int result = static_cast<int>(tooSmall);
        assert(false && "Should have thrown overflow_error");
    } catch (const std::overflow_error&) {
    }
    
    std::cout << "✅ testBigIntOverflowConversion: PASSED\n";
}

void testBigIntCompoundOperations() {
    bigint::BigInt a("100");
    

    a += 50;
    assert(a.toString() == "150");
    
    a -= 25;
    assert(a.toString() == "125");
    
    a *= 2;
    assert(a.toString() == "250");
    
    a /= 5;
    assert(a.toString() == "50");
    
    std::cout << "✅ testBigIntCompoundOperations: PASSED\n";
}

void testBigIntComparisonWithInt() {
    bigint::BigInt a(100);
    
    assert(a == 100);
    assert(a != 50);
    assert(a > 50);
    assert(a < 150);
    assert(a >= 100);
    assert(a <= 100);
    

    bigint::BigInt b(-50);
    assert(b == -50);
    assert(b > -100);
    assert(b < 0);
    
    std::cout << "✅ testBigIntComparisonWithInt: PASSED\n";
}

void testBigIntStringEdgeCases() {

    bigint::BigInt num1("0000123");
    assert(num1.toString() == "123");
    
    bigint::BigInt num2("-0000456");
    assert(num2.toString() == "-456");
    

    bigint::BigInt num3("");
    assert(num3.toString() == "0");
    

    bigint::BigInt num4("0000");
    assert(num4.toString() == "0");

    assert(num4 == bigint::BigInt(0));
    
    std::cout << "✅ testBigIntStringEdgeCases: PASSED\n";
}

void testBigIntDigitCount() {
    bigint::BigInt num1(0);
    assert(num1.digitCount() == 1);
    
    bigint::BigInt num2(9);
    assert(num2.digitCount() == 1);
    
    bigint::BigInt num3(10);
    assert(num3.digitCount() == 2);
    
    bigint::BigInt num4("123456789");
    assert(num4.digitCount() == 9);
    
    std::cout << "✅ testBigIntDigitCount: PASSED\n";
}

void testBigIntNegativeOperations() {

    bigint::BigInt a("-100");
    bigint::BigInt b("-50");
    

    bigint::BigInt c = a + b;
    assert(c.toString() == "-150");
    

    bigint::BigInt d = a - b;
    assert(d.toString() == "-50");
    

    bigint::BigInt e = a * b;
    assert(e.toString() == "5000");
    

    bigint::BigInt f = a / b;
    assert(f.toString() == "2");
    
    std::cout << "✅ testBigIntNegativeOperations: PASSED\n";
}

void testBigIntMixedSignOperations() {

    bigint::BigInt positive("100");
    bigint::BigInt negative("-50");
    

    assert((positive + negative).toString() == "50");
    

    assert((negative + positive).toString() == "50");
    

    assert((positive - negative).toString() == "150");
    

    assert((negative - positive).toString() == "-150");
    
    std::cout << "✅ testBigIntMixedSignOperations: PASSED\n";
}

void testBigIntInputStream() {

    std::istringstream iss("123456 -789 0");
    bigint::BigInt a, b, c;
    
    iss >> a >> b >> c;
    
    assert(a.toString() == "123456");
    assert(b.toString() == "-789");
    assert(c.toString() == "0");
    
    std::cout << "✅ testBigIntInputStream: PASSED\n";
}

void testBigIntAbsoluteValue() {
    bigint::BigInt positive(42);
    bigint::BigInt negative(-42);
    bigint::BigInt zero(0);
    

    assert(positive == bigint::BigInt(42));

    assert((-negative).toString() == "42");
    assert(zero == bigint::BigInt(0));
    
    std::cout << "✅ testBigIntAbsoluteValue: PASSED\n";
}

void testBigIntBoundaryComparisons() {

    bigint::BigInt zero(0);
    bigint::BigInt smallPositive(1);
    bigint::BigInt smallNegative(-1);
    

    assert(zero == zero);
    assert(zero >= zero);
    assert(zero <= zero);
    assert(smallPositive > zero);
    assert(smallNegative < zero);
    assert(zero < smallPositive);
    assert(zero > smallNegative);
    

    bigint::BigInt shortNum(99);
    bigint::BigInt longNum("100");
    
    assert(shortNum < longNum);
    assert(longNum > shortNum);
    assert(shortNum != longNum);
    
    std::cout << "✅ testBigIntBoundaryComparisons: PASSED\n";
}

void testBigIntLargeNumberOperations() {

    bigint::BigInt largePositive("1000000000000000000");
    bigint::BigInt largeNegative("-1000000000000000000");
    bigint::BigInt one(1);
    

    bigint::BigInt sum1 = largePositive + largeNegative;
    assert(sum1.toString() == "0");
    
    bigint::BigInt sum2 = largeNegative + largePositive;
    assert(sum2.toString() == "0");
    
    bigint::BigInt diff1 = largePositive - largeNegative;
    assert(diff1.toString() == "2000000000000000000");
    
    bigint::BigInt diff2 = largeNegative - largePositive;
    assert(diff2.toString() == "-2000000000000000000");
    

    bigint::BigInt product = largePositive * largeNegative;
    assert(product.toString() == "-1000000000000000000000000000000000000");
    
    std::cout << "✅ testBigIntLargeNumberOperations: PASSED\n";
}

void testBigIntVeryLargeNumbers() {

    bigint::BigInt a("99999999999999999999999999999999999999");
    bigint::BigInt b("1");
    bigint::BigInt c("100000000000000000000000000000000000000");
    

    bigint::BigInt sum = a + b;
    assert(sum.toString() == "100000000000000000000000000000000000000");
    

    bigint::BigInt diff = c - b;
    assert(diff.toString() == "99999999999999999999999999999999999999");
    

    bigint::BigInt product = a * bigint::BigInt(2);
    assert(product.toString() == "199999999999999999999999999999999999998");
    
    std::cout << "✅ testBigIntVeryLargeNumbers: PASSED\n";
}

void testBigIntBaseBoundary() {

    
    bigint::BigInt a("999");
    bigint::BigInt b("1000");
    bigint::BigInt c("1001");
    

    bigint::BigInt sum1 = a + bigint::BigInt(1);
    assert(sum1.toString() == "1000");
    
    bigint::BigInt sum2 = b + bigint::BigInt(1);
    assert(sum2.toString() == "1001");
    
    bigint::BigInt diff1 = c - bigint::BigInt(1);
    assert(diff1.toString() == "1000");
    
    bigint::BigInt diff2 = b - bigint::BigInt(1);
    assert(diff2.toString() == "999");
    
    std::cout << "✅ testBigIntBaseBoundary: PASSED\n";
}

void testBigIntComplexExpressions() {

    bigint::BigInt a("10");
    bigint::BigInt b("20");
    bigint::BigInt c("30");
    

    bigint::BigInt result1 = (a + b) * c;
    assert(result1.toString() == "900");
    

    bigint::BigInt result2 = a + (b * c);
    assert(result2.toString() == "610");
    

    bigint::BigInt result3 = (a - b) * c;
    assert(result3.toString() == "-300");
    

    bigint::BigInt result4 = a * b - c;
    assert(result4.toString() == "170");
    
    std::cout << "✅ testBigIntComplexExpressions: PASSED\n";
}

void testBigIntAssignmentChain() {

    bigint::BigInt a("100");
    bigint::BigInt b("50");
    bigint::BigInt c("25");
    
    a += b += c;
    assert(b.toString() == "75");
    assert(a.toString() == "175");
    
    a -= b -= c;
    assert(b.toString() == "50");
    assert(a.toString() == "125");
    
    std::cout << "✅ testBigIntAssignmentChain: PASSED\n";
}

void testBigIntSelfOperations() {

    bigint::BigInt a("42");
    
    a += a;
    assert(a.toString() == "84");
    
    a -= a;
    assert(a.toString() == "0");
    
    bigint::BigInt b("10");
    b *= b;
    assert(b.toString() == "100");
    
    bigint::BigInt c("100");
    c /= c;
    assert(c.toString() == "1");
    
    std::cout << "✅ testBigIntSelfOperations: PASSED\n";
}

void testBigIntNegativeZero() {

    bigint::BigInt zero(0);
    bigint::BigInt negZero = -zero;
    
    assert(negZero.toString() == "0");
    assert(!(negZero < zero));
    assert(!(negZero > zero));
    assert(negZero == zero);
    

    bigint::BigInt a("123");
    bigint::BigInt b = -(-a);
    assert(b.toString() == "123");
    
    std::cout << "✅ testBigIntNegativeZero: PASSED\n";
}

void testBigIntPrePostIncrementDifference() {

    bigint::BigInt a("10");
    bigint::BigInt b("10");
    
    bigint::BigInt c = ++a;
    bigint::BigInt d = b++;
    
    assert(a.toString() == "11");
    assert(b.toString() == "11");
    assert(c.toString() == "11");
    assert(d.toString() == "10");
    
    std::cout << "✅ testBigIntPrePostIncrementDifference: PASSED\n";
}

void testBigIntStringWithPlusSign() {

    bigint::BigInt a("+123");
    bigint::BigInt b("-456");
    bigint::BigInt c("+0");
    
    assert(a.toString() == "123");
    assert(b.toString() == "-456");
    assert(c.toString() == "0");
    

    bigint::BigInt result = a + b;
    assert(result.toString() == "-333");
    
    std::cout << "✅ testBigIntStringWithPlusSign: PASSED\n";
}

void runBigIntTests() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "RUNNING BIGINT TESTS\n";
    std::cout << std::string(50, '=') << "\n";
    
    testBigIntDefaultConstructor();
    testBigIntIntConstructor();
    testBigIntStringConstructor();
    testBigIntCharPtrConstructor();
    testBigIntAddition();
    testBigIntSubtraction();
    testBigIntMultiplication();
    testBigIntDivision();
    testBigIntAssignmentOperators();
    testBigIntIncrementDecrement();
    testBigIntComparison();
    testBigIntUnaryOperators();
    testBigIntIntConversion();
    testBigIntLargeNumbers();
    testBigIntZeroOperations();
    testBigIntWithIntOperations();
    testBigIntStreamOperators();
    testBigIntEdgeCases();
    testBigIntInvalidString();
    testBigIntDivisionByZero();
    testBigIntOverflowConversion();
    testBigIntCompoundOperations();
    testBigIntComparisonWithInt();
    testBigIntStringEdgeCases();
    testBigIntDigitCount();
    testBigIntNegativeOperations();
    testBigIntMixedSignOperations();
    testBigIntInputStream();
    testBigIntAbsoluteValue();
    testBigIntBoundaryComparisons();
    testBigIntLargeNumberOperations();
    testBigIntVeryLargeNumbers();
    testBigIntBaseBoundary();
    testBigIntComplexExpressions();
    testBigIntAssignmentChain();
    testBigIntSelfOperations();
    testBigIntNegativeZero();
    testBigIntPrePostIncrementDifference();
    testBigIntStringWithPlusSign();
    
    std::cout << std::string(50, '=') << "\n";
    std::cout << "ALL BIGINT TESTS PASSED! ✅\n";
    std::cout << std::string(50, '=') << "\n\n";
}
