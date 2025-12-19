#ifndef MINIMARKET_BANKING_ATM_HPP
#define MINIMARKET_BANKING_ATM_HPP

#include <string>

namespace minimarket {
namespace banking {

class ATM {
public:
    ATM(const std::string& id, const std::string& loc, double cash);
    bool dispenseCash(double amount);
    bool processDeposit(double amount);
    const std::string& getAtmId() const { return atmId; }
    const std::string& getLocation() const { return location; }
    double getCashBalance() const { return cashBalance; }

private:
    std::string atmId;
    std::string location;
    double cashBalance;
};

} // namespace banking
} // namespace minimarket

#endif
