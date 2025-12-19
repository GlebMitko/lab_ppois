#ifndef MINIMARKET_BANKING_FRAUDDETECTOR_HPP
#define MINIMARKET_BANKING_FRAUDDETECTOR_HPP

#include <string>
#include <vector>
#include "Transaction.hpp"

namespace minimarket {
namespace banking {

class FraudDetector {
public:
    FraudDetector(double threshold = 5000.0);
    bool detectFraud(const Transaction& transaction);
    void addSuspiciousPattern(const std::string& pattern);
    double getFraudThreshold() const { return fraudThreshold; }

private:
    double fraudThreshold;
    std::vector<std::string> suspiciousPatterns;
};

} // namespace banking
} // namespace minimarket

#endif
