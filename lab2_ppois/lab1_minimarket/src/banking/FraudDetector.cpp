#include "../../include/banking/FraudDetector.hpp"

namespace minimarket {
namespace banking {

FraudDetector::FraudDetector(double threshold) : fraudThreshold(threshold) {}

bool FraudDetector::detectFraud(const Transaction& transaction) {
    return transaction.getAmount() > fraudThreshold;
}

void FraudDetector::addSuspiciousPattern(const std::string& pattern) {
    suspiciousPatterns.push_back(pattern);
}

} // namespace banking
} // namespace minimarket
