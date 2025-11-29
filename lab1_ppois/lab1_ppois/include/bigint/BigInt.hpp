#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

namespace bigint {

class BigInt {
private:
    std::vector<int> digits;
    bool isNegative;
    static const int BASE = 10000;
    static const int BASE_DIGITS = 4;

public:
    BigInt();
    BigInt(int number);
    BigInt(const std::string& str);
    BigInt(const char* str);
    BigInt(const BigInt& other) = default;
    ~BigInt() = default;
    BigInt& operator=(const BigInt& other) = default;
    
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;
    
    BigInt& operator+=(const BigInt& other);
    BigInt& operator-=(const BigInt& other);
    BigInt& operator*=(const BigInt& other);
    BigInt& operator/=(const BigInt& other);
    
    BigInt operator+(int other) const;
    BigInt operator-(int other) const;
    BigInt operator*(int other) const;
    BigInt operator/(int other) const;
    
    BigInt& operator+=(int other);
    BigInt& operator-=(int other);
    BigInt& operator*=(int other);
    BigInt& operator/=(int other);
    
    BigInt operator-() const;
    BigInt operator+() const;
    
    BigInt& operator++();
    BigInt operator++(int);
    BigInt& operator--();
    BigInt operator--(int);
    
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    
    bool operator==(int other) const;
    bool operator!=(int other) const;
    bool operator<(int other) const;
    bool operator<=(int other) const;
    bool operator>(int other) const;
    bool operator>=(int other) const;
    
    explicit operator int() const;
    std::string toString() const;
    bool isZero() const;
    size_t digitCount() const;
    
    friend std::ostream& operator<<(std::ostream& os, const BigInt& num);
    friend std::istream& operator>>(std::istream& is, BigInt& num);

private:
    void normalize();
    void fromString(const std::string& str);
    void removeLeadingZeros();
    int compare(const BigInt& other) const;
    BigInt abs() const;
    void add(const BigInt& other);
    void subtract(const BigInt& other);
    void multiply(const BigInt& other);
    void divide(const BigInt& other);
    void multiplyByDigit(int digit);
    void shiftLeft(size_t positions);
};

}
