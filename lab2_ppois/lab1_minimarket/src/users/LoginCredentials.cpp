#include "../../include/users/LoginCredentials.hpp"
#include "../../include/utils/Exceptions.hpp"
#include <functional>

namespace minimarket {
namespace users {

LoginCredentials::LoginCredentials(const std::string& user, const std::string& password)
    : username(user), lastLogin(std::time(nullptr)) {
    passwordHash = std::to_string(std::hash<std::string>{}(password));
}

bool LoginCredentials::verifyPassword(const std::string& inputPassword) const {
    std::string inputHash = std::to_string(std::hash<std::string>{}(inputPassword));
    return inputHash == passwordHash;
}

void LoginCredentials::updatePassword(const std::string& newPassword) {
    if (newPassword.length() < 8) {
        throw exceptions::InvalidPasswordException("Password must be at least 8 characters");
    }
    passwordHash = std::to_string(std::hash<std::string>{}(newPassword));
    lastLogin = std::time(nullptr);
}

bool LoginCredentials::isPasswordExpired() const {
    std::time_t now = std::time(nullptr);
    double daysDiff = std::difftime(now, lastLogin) / (60 * 60 * 24);
    return daysDiff > 90;
}

} // namespace users
} // namespace minimarket
