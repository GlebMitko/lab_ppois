#ifndef MINIMARKET_USERS_USER_HPP
#define MINIMARKET_USERS_USER_HPP

#include <string>

namespace minimarket {
namespace users {

class User {
public:
    User(const std::string& id, const std::string& name, const std::string& email);
    bool authenticate(const std::string& password) const;
    std::string getUserRole() const;
    bool updateEmail(const std::string& newEmail);

    const std::string& getUserId() const { return userId; }
    const std::string& getUsername() const { return username; }
    const std::string& getEmail() const { return email; }

private:
    std::string userId;
    std::string username;
    std::string email;
};

} // namespace users
} // namespace minimarket

#endif
