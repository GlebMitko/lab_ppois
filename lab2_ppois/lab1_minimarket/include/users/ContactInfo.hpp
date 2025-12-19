#ifndef MINIMARKET_USERS_CONTACTINFO_HPP
#define MINIMARKET_USERS_CONTACTINFO_HPP

#include <string>

namespace minimarket {
namespace users {

class ContactInfo {
public:
    ContactInfo(const std::string& phone, const std::string& mail, const std::string& emergency);
    bool validateContactInfo() const;
    std::string getPrimaryContact() const;
    bool hasEmergencyContact() const;

    const std::string& getPhoneNumber() const { return phoneNumber; }
    const std::string& getEmail() const { return email; }
    const std::string& getEmergencyContact() const { return emergencyContact; }

private:
    std::string phoneNumber;
    std::string email;
    std::string emergencyContact;
};

} // namespace users
} // namespace minimarket

#endif
