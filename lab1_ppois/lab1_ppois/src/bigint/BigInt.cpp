#include "../../include/bigint/BigInt.hpp"
#include "../../include/utils/StringUtils.hpp"
#include <algorithm>
#include <sstream>
#include <cmath>

namespace bigint {

BigInt::BigInt() : isNegative(false) {
    digits.push_back(0);
}

BigInt::BigInt(int number) : isNegative(number < 0) {
    if (number == 0) {
        digits.push_back(0);
        return;
    }
    
    long long absNumber = std::abs(static_cast<long long>(number));
    while (absNumber > 0) {
        digits.push_back(absNumber % BASE);
        absNumber /= BASE;
    }
}

BigInt::BigInt(const std::string& str) {
    fromString(str);
}

BigInt::BigInt(const char* str) {
    fromString(std::string(str));
}

BigInt BigInt::operator+(const BigInt& other) const {
    BigInt result(*this);
    result += other;
    return result;
}

BigInt BigInt::operator-(const BigInt& other) const {
    BigInt result(*this);
    result -= other;
    return result;
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt result(*this);
    result *= other;
    return result;
}

BigInt BigInt::operator/(const BigInt& other) const {
    BigInt result(*this);
    result /= other;
    return result;
}

BigInt& BigInt::operator+=(const BigInt& other) {
    if (isNegative == other.isNegative) {
        add(other);
    } else {
        if (abs() >= other.abs()) {
            subtract(other);
        } else {
            BigInt temp(other);
            temp.subtract(*this);
            *this = temp;
            isNegative = other.isNegative;
        }
    }
    normalize();
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& other) {
    if (isNegative != other.isNegative) {
        add(other);
    } else {
        if (abs() >= other.abs()) {
            subtract(other);
        } else {
            BigInt temp(other);
            temp.subtract(*this);
            *this = temp;
            isNegative = !isNegative;
        }
    }
    normalize();
    return *this;
}

BigInt& BigInt::operator*=(const BigInt& other) {
    multiply(other);
    normalize();
    return *this;
}

BigInt& BigInt::operator/=(const BigInt& other) {
    if (other.isZero()) {
        throw std::runtime_error("Division by zero");
    }
    
    divide(other);
    normalize();
    return *this;
}

BigInt BigInt::operator+(int other) const {
    return *this + BigInt(other);
}

BigInt BigInt::operator-(int other) const {
    return *this - BigInt(other);
}

BigInt BigInt::operator*(int other) const {
    return *this * BigInt(other);
}

BigInt BigInt::operator/(int other) const {
    return *this / BigInt(other);
}

BigInt& BigInt::operator+=(int other) {
    return *this += BigInt(other);
}

BigInt& BigInt::operator-=(int other) {
    return *this -= BigInt(other);
}

BigInt& BigInt::operator*=(int other) {
    return *this *= BigInt(other);
}

BigInt& BigInt::operator/=(int other) {
    return *this /= BigInt(other);
}

BigInt BigInt::operator-() const {
    BigInt result(*this);
    if (!result.isZero()) {
        result.isNegative = !result.isNegative;
    }
    return result;
}

BigInt BigInt::operator+() const {
    return *this;
}

BigInt& BigInt::operator++() {
    *this += 1;
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt temp(*this);
    ++(*this);
    return temp;
}

BigInt& BigInt::operator--() {
    *this -= 1;
    return *this;
}

BigInt BigInt::operator--(int) {
    BigInt temp(*this);
    --(*this);
    return temp;
}

bool BigInt::operator==(const BigInt& other) const {
    return compare(other) == 0;
}

bool BigInt::operator!=(const BigInt& other) const {
    return compare(other) != 0;
}

bool BigInt::operator<(const BigInt& other) const {
    return compare(other) < 0;
}

bool BigInt::operator<=(const BigInt& other) const {
    return compare(other) <= 0;
}

bool BigInt::operator>(const BigInt& other) const {
    return compare(other) > 0;
}

bool BigInt::operator>=(const BigInt& other) const {
    return compare(other) >= 0;
}

bool BigInt::operator==(int other) const {
    return *this == BigInt(other);
}

bool BigInt::operator!=(int other) const {
    return *this != BigInt(other);
}

bool BigInt::operator<(int other) const {
    return *this < BigInt(other);
}

bool BigInt::operator<=(int other) const {
    return *this <= BigInt(other);
}

bool BigInt::operator>(int other) const {
    return *this > BigInt(other);
}

bool BigInt::operator>=(int other) const {
    return *this >= BigInt(other);
}

BigInt::operator int() const {
    if (*this > BigInt(INT_MAX) || *this < BigInt(INT_MIN)) {
        throw std::overflow_error("BigInt too large for int conversion");
    }
    
    int result = 0;
    int multiplier = 1;
    
    for (size_t i = 0; i < digits.size(); ++i) {
        result += digits[i] * multiplier;
        multiplier *= BASE;
    }
    
    return isNegative ? -result : result;
}

std::string BigInt::toString() const {
    if (isZero()) {
        return "0";
    }
    
    std::stringstream ss;
    if (isNegative) {
        ss << "-";
    }
    
    ss << digits.back();
    
    for (int i = static_cast<int>(digits.size()) - 2; i >= 0; --i) {
        ss.width(BASE_DIGITS);
        ss.fill('0');
        ss << digits[i];
    }
    
    return ss.str();
}

bool BigInt::isZero() const {
    return digits.size() == 1 && digits[0] == 0;
}

size_t BigInt::digitCount() const {
    if (isZero()) return 1;
    
    size_t count = (digits.size() - 1) * BASE_DIGITS;
    int lastDigit = digits.back();
    
    while (lastDigit > 0) {
        count++;
        lastDigit /= 10;
    }
    
    return count;
}

void BigInt::normalize() {
    removeLeadingZeros();
    if (isZero()) {
        isNegative = false;
    }
}

void BigInt::fromString(const std::string& str) {
    digits.clear();
    isNegative = false;
    
    if (str.empty()) {
        digits.push_back(0);
        return;
    }
    
    size_t start = 0;
    if (str[0] == '-') {
        isNegative = true;
        start = 1;
    } else if (str[0] == '+') {
        start = 1;
    }
    
    while (start < str.size() && str[start] == '0') {
        start++;
    }
    
    if (start == str.size()) {
        digits.push_back(0);
        isNegative = false;
        return;
    }
    
    for (int i = str.size() - 1; i >= static_cast<int>(start); i -= BASE_DIGITS) {
        int digit = 0;
        int power = 1;
        
        for (int j = 0; j < BASE_DIGITS; ++j) {
            int pos = i - j;
            if (pos < static_cast<int>(start)) break;
            
            if (!std::isdigit(str[pos])) {
                throw std::invalid_argument("Invalid character in BigInt string");
            }
            
            digit += (str[pos] - '0') * power;
            power *= 10;
        }
        
        digits.push_back(digit);
    }
    
    normalize();
}

void BigInt::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

int BigInt::compare(const BigInt& other) const {
    if (isNegative != other.isNegative) {
        return isNegative ? -1 : 1;
    }
    
    if (digits.size() != other.digits.size()) {
        return (digits.size() > other.digits.size() ? 1 : -1) * (isNegative ? -1 : 1);
    }
    
    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return (digits[i] > other.digits[i] ? 1 : -1) * (isNegative ? -1 : 1);
        }
    }
    
    return 0;
}

BigInt BigInt::abs() const {
    BigInt result(*this);
    result.isNegative = false;
    return result;
}

void BigInt::add(const BigInt& other) {
    size_t maxSize = std::max(digits.size(), other.digits.size());
    digits.resize(maxSize, 0);
    
    int carry = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        int sum = digits[i] + carry;
        if (i < other.digits.size()) {
            sum += other.digits[i];
        }
        
        digits[i] = sum % BASE;
        carry = sum / BASE;
    }
    
    if (carry > 0) {
        digits.push_back(carry);
    }
}

void BigInt::subtract(const BigInt& other) {
    int borrow = 0;
    for (size_t i = 0; i < digits.size(); ++i) {
        int diff = digits[i] - borrow;
        if (i < other.digits.size()) {
            diff -= other.digits[i];
        }
        
        if (diff < 0) {
            diff += BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        digits[i] = diff;
    }
    
    removeLeadingZeros();
}

void BigInt::multiply(const BigInt& other) {
    BigInt result;
    result.digits.resize(digits.size() + other.digits.size(), 0);
    result.isNegative = isNegative != other.isNegative;
    
    for (size_t i = 0; i < digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.digits.size() || carry > 0; ++j) {
            long long product = result.digits[i + j] + 
                               static_cast<long long>(digits[i]) * 
                               (j < other.digits.size() ? other.digits[j] : 0) + 
                               carry;
            
            result.digits[i + j] = product % BASE;
            carry = product / BASE;
        }
    }
    
    result.normalize();
    *this = result;
}

void BigInt::divide(const BigInt& other) {
    if (other.isZero()) {
        throw std::runtime_error("Division by zero");
    }
    
    BigInt a = abs();
    BigInt b = other.abs();
    
    if (a < b) {
        *this = BigInt(0);
        return;
    }
    
    BigInt result;
    result.digits.resize(a.digits.size() - b.digits.size() + 1, 0);
    result.isNegative = isNegative != other.isNegative;
    
    BigInt current;
    for (int i = static_cast<int>(a.digits.size()) - 1; i >= 0; --i) {
        current.shiftLeft(1);
        current.digits[0] = a.digits[i];
        current.normalize();
        
        int left = 0, right = BASE;
        while (left < right) {
            int mid = (left + right + 1) / 2;
            BigInt product = b * mid;
            
            if (product <= current) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        
        if (i < static_cast<int>(result.digits.size())) {
            result.digits[i] = left;
        }
        
        current -= b * left;
    }
    
    result.normalize();
    *this = result;
}

void BigInt::multiplyByDigit(int digit) {
    int carry = 0;
    for (size_t i = 0; i < digits.size(); ++i) {
        long long product = static_cast<long long>(digits[i]) * digit + carry;
        digits[i] = product % BASE;
        carry = product / BASE;
    }
    
    if (carry > 0) {
        digits.push_back(carry);
    }
}

void BigInt::shiftLeft(size_t positions) {
    if (isZero()) return;
    
    digits.insert(digits.begin(), positions, 0);
}

std::ostream& operator<<(std::ostream& os, const BigInt& num) {
    os << num.toString();
    return os;
}

std::istream& operator>>(std::istream& is, BigInt& num) {
    std::string str;
    is >> str;
    num.fromString(str);
    return is;
}

}
