#ifndef MINIMARKET_USERS_USERSESSION_HPP
#define MINIMARKET_USERS_USERSESSION_HPP

#include <string>
#include <ctime>

namespace minimarket {
namespace users {

class UserSession {
public:
    UserSession(const std::string& sessId, const std::string& uid);
    bool isSessionValid() const;
    void refreshSession();
    int calculateSessionDuration() const;

    const std::string& getSessionId() const { return sessionId; }
    const std::string& getUserId() const { return userId; }

private:
    std::string sessionId;
    std::string userId;
    std::time_t startTime;
    std::time_t lastActivity;
};

} // namespace users
} // namespace minimarket

#endif
