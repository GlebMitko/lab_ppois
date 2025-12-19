#ifndef MINIMARKET_USERS_LOGINCREDENTIALS_HPP
#define MINIMARKET_USERS_LOGINCREDENTIALS_HPP

#include <string>
#include <ctime>

namespace minimarket {
namespace users {

class LoginCredentials {
public:
    LoginCredentials(const std::string& user, const std::string& password);
    bool verifyPassword(const std::string& inputPassword) const;
    void updatePassword(const std::string& newPassword);
    bool isPasswordExpired() const;

    const std::string& getUsername() const { return username; }

private:
    std::string username;
    std::string passwordHash;
    std::time_t lastLogin;
};

} // namespace users
} // namespace minimarket

#endif
