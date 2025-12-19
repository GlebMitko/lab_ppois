#ifndef MINIMARKET_BANKING_CREDITCARD_HPP
#define MINIMARKET_BANKING_CREDITCARD_HPP

#include "Card.hpp"

namespace minimarket {
namespace banking {

class CreditCard : public Card {
public:
    CreditCard(const std::string& number, const std::string& name, const std::string& expiry, double limit)
        : Card(number, name, expiry), creditLimit(limit), usedCredit(0.0) {}

    bool useCredit(double amount);
    double calculateAvailableCredit() const;
    double getCreditLimit() const { return creditLimit; }
    double getUsedCredit() const { return usedCredit; }

private:
    double creditLimit;
    double usedCredit;
};

} // namespace banking
} // namespace minimarket

#endif
