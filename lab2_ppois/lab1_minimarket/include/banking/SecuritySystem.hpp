#ifndef MINIMARKET_BANKING_SECURITYSYSTEM_HPP
#define MINIMARKET_BANKING_SECURITYSYSTEM_HPP

#include <string>
#include <vector>

namespace minimarket {
namespace banking {

class SecuritySystem {
public:
    SecuritySystem(int level = 2);
    bool authenticateUser(const std::string& credentials);
    void logSecurityEvent(const std::string& event);
    int getSecurityLevel() const { return securityLevel; }

private:
    int securityLevel;
    std::vector<std::string> accessLogs;
};

} // namespace banking
} // namespace minimarket

#endif
