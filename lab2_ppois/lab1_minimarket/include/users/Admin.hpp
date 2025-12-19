#ifndef MINIMARKET_USERS_ADMIN_HPP
#define MINIMARKET_USERS_ADMIN_HPP

#include <string>
#include <vector>
#include "User.hpp"

namespace minimarket {
namespace users {

class Admin : public User {
public:
    Admin(const std::string& id, const std::string& name, const std::string& email, const std::string& level);
    bool grantPermissions(const std::string& permission);
    bool revokeUserAccess(const std::string& targetUserId);
    bool canModifySystemSettings() const;

    const std::string& getAdminLevel() const { return adminLevel; }
    const std::vector<std::string>& getPermissions() const { return permissions; }

private:
    std::string adminLevel;
    std::vector<std::string> permissions;
};

} // namespace users
} // namespace minimarket

#endif
