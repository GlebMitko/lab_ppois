#ifndef MINIMARKET_BANKING_CUSTOMERSERVICE_HPP
#define MINIMARKET_BANKING_CUSTOMERSERVICE_HPP

#include <string>

namespace minimarket {
namespace banking {

class CustomerService {
public:
    CustomerService(const std::string& dept, int agents);
    bool handleComplaint(const std::string& complaint);
    int estimateWaitTime(int queueLength) const;
    const std::string& getDepartment() const { return department; }
    int getAvailableAgents() const { return availableAgents; }

private:
    std::string department;
    int availableAgents;
};

} // namespace banking
} // namespace minimarket

#endif
