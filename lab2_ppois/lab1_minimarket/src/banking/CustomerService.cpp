#include "../../include/banking/CustomerService.hpp"

namespace minimarket {
namespace banking {

CustomerService::CustomerService(const std::string& dept, int agents)
    : department(dept), availableAgents(agents) {}

bool CustomerService::handleComplaint(const std::string& complaint) {
    return !complaint.empty() && availableAgents > 0;
}

int CustomerService::estimateWaitTime(int queueLength) const {
    return queueLength * 5;
}

} // namespace banking
} // namespace minimarket
