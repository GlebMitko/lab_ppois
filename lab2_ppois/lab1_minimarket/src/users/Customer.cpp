#include "../../include/users/Customer.hpp"
#include <cmath>

namespace minimarket {
namespace users {

Customer::Customer(const std::string& id, const std::string& name,
                   const std::string& email, const std::string& phone)
    : User(id, name, email), customerId(id), phoneNumber(phone), registrationDate(std::time(nullptr)) {}

bool Customer::validatePhoneNumber() const {
    return phoneNumber.length() >= 10 &&
           phoneNumber.find_first_not_of("0123456789+- ()") == std::string::npos;
}

int Customer::calculateLoyaltyYears() const {
    std::time_t now = std::time(nullptr);
    double secondsDiff = std::difftime(now, registrationDate);
    return static_cast<int>(secondsDiff / (365.25 * 24 * 60 * 60));
}

bool Customer::canApplyForPremium() const {
    return calculateLoyaltyYears() >= 2 && validatePhoneNumber();
}

} // namespace users
} // namespace minimarket
