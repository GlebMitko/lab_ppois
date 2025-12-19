#include "../../include/banking/AuditTrail.hpp"

namespace minimarket {
namespace banking {

AuditTrail::AuditTrail() {}

void AuditTrail::recordTransaction(const Transaction& transaction) {
    auditRecords.push_back(transaction.generateReceipt());
}

bool AuditTrail::verifyCompliance() const {
    return auditRecords.size() <= 1000;
}

} // namespace banking
} // namespace minimarket
