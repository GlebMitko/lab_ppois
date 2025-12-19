#ifndef MINIMARKET_USERS_EMPLOYEE_HPP
#define MINIMARKET_USERS_EMPLOYEE_HPP

#include <string>
#include "User.hpp"

namespace minimarket {
namespace users {

class Employee : public User {
public:
    Employee(const std::string& id, const std::string& name, const std::string& email,
             const std::string& dept, double sal);
    bool approveLoanApplication(double amount) const;
    double calculateAnnualBonus() const;
    bool canAccessSensitiveData() const;

    const std::string& getDepartment() const { return department; }
    double getSalary() const { return salary; }

private:
    std::string employeeId;
    std::string department;
    double salary;
};

} // namespace users
} // namespace minimarket

#endif
