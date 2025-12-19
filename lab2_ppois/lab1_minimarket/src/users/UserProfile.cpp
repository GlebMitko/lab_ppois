#include "../../include/users/UserProfile.hpp"
#include <ctime>

namespace minimarket {
namespace users {

UserProfile::UserProfile(const std::string& id, const std::string& first,
                         const std::string& last, const std::string& dob)
    : userId(id), firstName(first), lastName(last), dateOfBirth(dob) {}

int UserProfile::calculateAge() const {
    if (dateOfBirth.length() != 10) return 0;
    int birthYear = std::stoi(dateOfBirth.substr(6, 4));
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    int currentYear = localTime->tm_year + 1900;
    return currentYear - birthYear;
}

std::string UserProfile::getFullName() const {
    return firstName + " " + lastName;
}

bool UserProfile::isAdult() const {
    return calculateAge() >= 18;
}

} // namespace users
} // namespace minimarket
