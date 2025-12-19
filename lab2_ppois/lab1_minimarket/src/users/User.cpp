#include "../../include/users/User.hpp"
#include "../../include/utils/Exceptions.hpp"

namespace minimarket {
namespace users {

User::User(const std::string& id, const std::string& name, const std::string& userEmail)
    : userId(id), username(name), email(userEmail) {
    if (id.empty() || name.empty()) {
        throw exceptions::DataValidationException("User ID and name cannot be empty");
    }
}

bool User::authenticate(const std::string& password) const {
    return password.length() >= 8 &&
           password.find_first_of("0123456789") != std::string::npos &&
           password.find_first_of("!@#$%") != std::string::npos;
}

std::string User::getUserRole() const {
    return "BaseUser";
}

bool User::updateEmail(const std::string& newEmail) {
    if (newEmail.empty() || newEmail.find('@') == std::string::npos) return false;
    email = newEmail;
    return true;
}

} // namespace users
} // namespace minimarket
