#ifndef MINIMARKET_USERS_CUSTOMER_HPP
#define MINIMARKET_USERS_CUSTOMER_HPP

#include <string>
#include <ctime>
#include "User.hpp"

namespace minimarket {
namespace users {

class Customer : public User {
public:
    Customer(const std::string& id, const std::string& name, const std::string& email, const std::string& phone);
    bool validatePhoneNumber() const;
    int calculateLoyaltyYears() const;
    bool canApplyForPremium() const;

    const std::string& getPhoneNumber() const { return phoneNumber; }

private:
    std::string customerId;
    std::string phoneNumber;
    std::time_t registrationDate;
};

} // namespace users
} // namespace minimarket

#endif
