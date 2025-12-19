#ifndef MINIMARKET_BANKING_NOTIFICATIONSERVICE_HPP
#define MINIMARKET_BANKING_NOTIFICATIONSERVICE_HPP

#include <string>
#include <vector>

namespace minimarket {
namespace banking {

class NotificationService {
public:
    NotificationService();
    bool sendAlert(const std::string& message, const std::string& channel);
    void scheduleReminder(const std::string& reminder, std::time_t time);

private:
    std::vector<std::string> notificationChannels;
};

} // namespace banking
} // namespace minimarket

#endif
