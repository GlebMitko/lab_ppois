#include "../../include/users/Admin.hpp"

namespace minimarket {
namespace users {

Admin::Admin(const std::string& id, const std::string& name,
             const std::string& email, const std::string& level)
    : User(id, name, email), adminLevel(level) {}

bool Admin::grantPermissions(const std::string& permission) {
    if (permission.empty()) return false;
    permissions.push_back(permission);
    return true;
}

bool Admin::revokeUserAccess(const std::string& targetUserId) {
    return !targetUserId.empty() && adminLevel == "SuperAdmin";
}

bool Admin::canModifySystemSettings() const {
    return adminLevel == "SuperAdmin" || adminLevel == "SystemAdmin";
}

} // namespace users
} // namespace minimarket
