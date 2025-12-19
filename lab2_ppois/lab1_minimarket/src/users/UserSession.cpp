#include "../../include/users/UserSession.hpp"

namespace minimarket {
namespace users {

UserSession::UserSession(const std::string& sessId, const std::string& uid)
    : sessionId(sessId), userId(uid), startTime(std::time(nullptr)), lastActivity(std::time(nullptr)) {}

bool UserSession::isSessionValid() const {
    std::time_t now = std::time(nullptr);
    double minutesDiff = std::difftime(now, lastActivity) / 60;
    return minutesDiff < 30;
}

void UserSession::refreshSession() {
    lastActivity = std::time(nullptr);
}

int UserSession::calculateSessionDuration() const {
    return static_cast<int>(std::difftime(lastActivity, startTime) / 60);
}

} // namespace users
} // namespace minimarket
