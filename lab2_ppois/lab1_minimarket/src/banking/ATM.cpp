#include "../../include/banking/ATM.hpp"

namespace minimarket {
namespace banking {

ATM::ATM(const std::string& id, const std::string& loc, double cash)
    : atmId(id), location(loc), cashBalance(cash) {}

bool ATM::dispenseCash(double amount) {
    if (amount <= 0 || amount > cashBalance || amount > 1000) return false;
    cashBalance -= amount;
    return true;
}

bool ATM::processDeposit(double amount) {
    if (amount <= 0) return false;
    cashBalance += amount;
    return true;
}

} // namespace banking
} // namespace minimarket
