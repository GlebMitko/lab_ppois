#include "../../include/users/ContactInfo.hpp"

namespace minimarket {
namespace users {

ContactInfo::ContactInfo(const std::string& phone, const std::string& mail,
                         const std::string& emergency)
    : phoneNumber(phone), email(mail), emergencyContact(emergency) {}

bool ContactInfo::validateContactInfo() const {
    bool validEmail = !email.empty() && email.find('@') != std::string::npos;
    bool validPhone = !phoneNumber.empty() && phoneNumber.length() >= 10;
    return validEmail && validPhone;
}

std::string ContactInfo::getPrimaryContact() const {
    return !phoneNumber.empty() ? phoneNumber : email;
}

bool ContactInfo::hasEmergencyContact() const {
    return !emergencyContact.empty();
}

} // namespace users
} // namespace minimarket
