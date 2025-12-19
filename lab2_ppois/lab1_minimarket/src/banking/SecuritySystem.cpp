#include "../../include/banking/SecuritySystem.hpp"

namespace minimarket {
namespace banking {

SecuritySystem::SecuritySystem(int level) : securityLevel(level) {}

bool SecuritySystem::authenticateUser(const std::string& credentials) {
    return credentials.length() >= 8 && securityLevel >= 2;
}

void SecuritySystem::logSecurityEvent(const std::string& event) {
    accessLogs.push_back(event);
}

} // namespace banking
} // namespace minimarket
