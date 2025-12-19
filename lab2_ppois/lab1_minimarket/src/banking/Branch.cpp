#include "../../include/banking/Branch.hpp"

namespace minimarket {
namespace banking {

Branch::Branch(const std::string& id, const std::string& address, const std::string& manager)
    : branchId(id), address(address), managerName(manager) {}

bool Branch::addAccount(const std::shared_ptr<Account>& account) {
    if (!account) return false;
    localAccounts.push_back(account);
    return true;
}

size_t Branch::getAccountCount() const {
    return localAccounts.size();
}

} // namespace banking
} // namespace minimarket
