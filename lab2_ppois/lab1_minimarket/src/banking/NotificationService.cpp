#include "../../include/banking/NotificationService.hpp"
#include <algorithm>

namespace minimarket {
namespace banking {

NotificationService::NotificationService() {
    notificationChannels = {"SMS", "Email", "Push"};
}

bool NotificationService::sendAlert(const std::string& message, const std::string& channel) {
    return !message.empty() && std::find(notificationChannels.begin(),
           notificationChannels.end(), channel) != notificationChannels.end();
}

void NotificationService::scheduleReminder(const std::string& reminder, std::time_t time) {
    // Stub
}

} // namespace banking
} // namespace minimarket
