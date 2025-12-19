#include "../../include/users/Employee.hpp"

namespace minimarket {
namespace users {

Employee::Employee(const std::string& id, const std::string& name,
                   const std::string& email, const std::string& dept, double sal)
    : User(id, name, email), employeeId(id), department(dept), salary(sal) {}

bool Employee::approveLoanApplication(double amount) const {
    return department == "Loans" && salary > 30000 && amount <= 100000;
}

double Employee::calculateAnnualBonus() const {
    return salary * 0.15;
}

bool Employee::canAccessSensitiveData() const {
    return department == "HR" || department == "Finance" || department == "IT";
}

} // namespace users
} // namespace minimarket
