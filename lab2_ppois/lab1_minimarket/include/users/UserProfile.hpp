#ifndef MINIMARKET_USERS_USERPROFILE_HPP
#define MINIMARKET_USERS_USERPROFILE_HPP

#include <string>

namespace minimarket {
namespace users {

class UserProfile {
public:
    UserProfile(const std::string& id, const std::string& first, const std::string& last, const std::string& dob);
    int calculateAge() const;
    std::string getFullName() const;
    bool isAdult() const;

    const std::string& getUserId() const { return userId; }
    const std::string& getFirstName() const { return firstName; }
    const std::string& getLastName() const { return lastName; }
    const std::string& getDateOfBirth() const { return dateOfBirth; }

private:
    std::string userId;
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
};

} // namespace users
} // namespace minimarket

#endif
