#ifndef MINIMARKET_BANKING_BRANCH_HPP
#define MINIMARKET_BANKING_BRANCH_HPP

#include <string>
#include <vector>
#include <memory>
#include "Account.hpp"

namespace minimarket {
namespace banking {

class Branch {
public:
    Branch(const std::string& id, const std::string& address, const std::string& manager);
    bool addAccount(const std::shared_ptr<Account>& account);
    size_t getAccountCount() const;
    const std::string& getBranchId() const { return branchId; }
    const std::string& getAddress() const { return address; }
    const std::string& getManagerName() const { return managerName; }

private:
    std::string branchId;
    std::string address;
    std::string managerName;
    std::vector<std::shared_ptr<Account>> localAccounts;
};

} // namespace banking
} // namespace minimarket

#endif
