#ifndef MINIMARKET_BANKING_AUDITTRAIL_HPP
#define MINIMARKET_BANKING_AUDITTRAIL_HPP

#include <string>
#include <vector>
#include "Transaction.hpp"

namespace minimarket {
namespace banking {

class AuditTrail {
public:
    AuditTrail();
    void recordTransaction(const Transaction& transaction);
    bool verifyCompliance() const;
    size_t getRecordCount() const { return auditRecords.size(); }

private:
    std::vector<std::string> auditRecords;
};

} // namespace banking
} // namespace minimarket

#endif
