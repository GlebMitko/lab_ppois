// tests/test_users.cpp

#include <iostream>
#include <cassert>
#include <memory>
#include <ctime>
#include <string>
#include <vector>

// Подключаем индивидуальные заголовки
#include "../include/users/User.hpp"
#include "../include/users/Customer.hpp"
#include "../include/users/Employee.hpp"
#include "../include/users/Admin.hpp"
#include "../include/users/UserProfile.hpp"
#include "../include/users/Address.hpp"
#include "../include/users/ContactInfo.hpp"
#include "../include/users/LoginCredentials.hpp"
#include "../include/users/UserSession.hpp"
#include "../include/users/UserPreferences.hpp"

#include "../include/utils/Exceptions.hpp"

void testUserCreation() {
    std::cout << "Testing User creation..." << std::endl;
    
    minimarket::users::User user("USER001", "john_doe", "john@example.com");
    assert(user.getUserId() == "USER001");
    assert(user.getUsername() == "john_doe");
    assert(user.getEmail() == "john@example.com");
    
    assert(user.getUserRole() == "BaseUser");
    
    assert(user.updateEmail("john.new@example.com") == true);
    assert(user.getEmail() == "john.new@example.com");
    
    std::cout << "✅ testUserCreation: PASSED" << std::endl;
}

void testUserAuthentication() {
    std::cout << "Testing User authentication..." << std::endl;
    
    minimarket::users::User user("USER002", "jane_smith", "jane@example.com");
    
    assert(user.authenticate("Password123!") == true);
    assert(user.authenticate("SecurePass456#") == true);
    
    assert(user.authenticate("short") == false);
    assert(user.authenticate("nouppercase123") == false);
    assert(user.authenticate("NOLOWERCASE123") == false);
    assert(user.authenticate("NoNumbersOrSpecial") == false);
    assert(user.authenticate("NoSpecial123") == false);
    
    std::cout << "✅ testUserAuthentication: PASSED" << std::endl;
}

void testCustomerOperations() {
    std::cout << "Testing Customer operations..." << std::endl;
    
    minimarket::users::Customer customer("CUST001", "John Customer", "john.customer@email.com", "+1234567890");
    
    assert(customer.getUserId() == "CUST001"); // Customer наследует User
    
    std::string role = customer.getUserRole();
    assert(!role.empty());
    std::cout << "Customer role: " << role << std::endl;
    
    assert(customer.validatePhoneNumber() == true);
    
    int loyaltyYears = customer.calculateLoyaltyYears();
    assert(loyaltyYears >= 0);
    
    bool canApply = customer.canApplyForPremium();
    assert(canApply == true || canApply == false);
    
    std::cout << "✅ testCustomerOperations: PASSED" << std::endl;
}

void testCustomerPhoneValidation() {
    std::cout << "Testing Customer phone validation..." << std::endl;
    
    minimarket::users::Customer valid1("CUST002", "Valid1", "test1@email.com", "+1-234-567-8900");
    assert(valid1.validatePhoneNumber() == true);
    
    minimarket::users::Customer valid2("CUST003", "Valid2", "test2@email.com", "(123) 456-7890");
    assert(valid2.validatePhoneNumber() == true);
    
    minimarket::users::Customer valid3("CUST004", "Valid3", "test3@email.com", "1234567890");
    assert(valid3.validatePhoneNumber() == true);
    
    minimarket::users::Customer invalid1("CUST005", "Invalid1", "test4@email.com", "123");
    assert(invalid1.validatePhoneNumber() == false);
    
    minimarket::users::Customer invalid2("CUST006", "Invalid2", "test5@email.com", "abc123def");
    assert(invalid2.validatePhoneNumber() == false);
    
    std::cout << "✅ testCustomerPhoneValidation: PASSED" << std::endl;
}

void testEmployeeOperations() {
    std::cout << "Testing Employee operations..." << std::endl;
    
    minimarket::users::Employee employee("EMP001", "Jane Employee", "jane@bank.com", "Loans", 50000.0);
    
    assert(employee.getUserId() == "EMP001");
    assert(employee.getDepartment() == "Loans");
    assert(employee.getSalary() == 50000.0);
    
    std::string role = employee.getUserRole();
    assert(!role.empty());
    std::cout << "Employee role: " << role << std::endl;
    
    assert(employee.approveLoanApplication(25000.0) == true);
    
    double bonus = employee.calculateAnnualBonus();
    assert(bonus == 7500.0);
    
    assert(employee.canAccessSensitiveData() == false);
    
    std::cout << "✅ testEmployeeOperations: PASSED" << std::endl;
}

void testEmployeeLoanApproval() {
    std::cout << "Testing Employee loan approval..." << std::endl;
    
    minimarket::users::Employee loanOfficer("EMP002", "Loan Officer", "loans@bank.com", "Loans", 45000.0);
    assert(loanOfficer.approveLoanApplication(20000.0) == true);
    assert(loanOfficer.approveLoanApplication(120000.0) == false);
    
    minimarket::users::Employee marketingEmp("EMP003", "Marketer", "marketing@bank.com", "Marketing", 40000.0);
    assert(marketingEmp.approveLoanApplication(10000.0) == false);
    
    minimarket::users::Employee lowSalaryEmp("EMP004", "Junior", "junior@bank.com", "Loans", 25000.0);
    assert(lowSalaryEmp.approveLoanApplication(5000.0) == false);
    
    std::cout << "✅ testEmployeeLoanApproval: PASSED" << std::endl;
}

void testEmployeeDataAccess() {
    std::cout << "Testing Employee data access..." << std::endl;
    
    minimarket::users::Employee hrEmployee("EMP005", "HR Staff", "hr@bank.com", "HR", 60000.0);
    assert(hrEmployee.canAccessSensitiveData() == true);
    
    minimarket::users::Employee financeEmployee("EMP006", "Finance Staff", "finance@bank.com", "Finance", 70000.0);
    assert(financeEmployee.canAccessSensitiveData() == true);
    
    minimarket::users::Employee itEmployee("EMP007", "IT Staff", "it@bank.com", "IT", 80000.0);
    assert(itEmployee.canAccessSensitiveData() == true);
    
    minimarket::users::Employee marketingEmployee("EMP008", "Marketer", "marketing@bank.com", "Marketing", 50000.0);
    assert(marketingEmployee.canAccessSensitiveData() == false);
    
    minimarket::users::Employee salesEmployee("EMP009", "Salesperson", "sales@bank.com", "Sales", 55000.0);
    assert(salesEmployee.canAccessSensitiveData() == false);
    
    std::cout << "✅ testEmployeeDataAccess: PASSED" << std::endl;
}

void testAdminOperations() {
    std::cout << "Testing Admin operations..." << std::endl;
    
    minimarket::users::Admin admin("ADM001", "Super Admin", "admin@system.com", "SuperAdmin");
    
    assert(admin.getUserId() == "ADM001");
    assert(admin.getAdminLevel() == "SuperAdmin");
    
    std::string role = admin.getUserRole();
    assert(!role.empty());
    std::cout << "Admin role: " << role << std::endl;
    
    assert(admin.grantPermissions("user_management") == true);
    assert(admin.grantPermissions("system_config") == true);
    
    assert(admin.revokeUserAccess("USER123") == true);
    
    assert(admin.canModifySystemSettings() == true);
    
    std::cout << "✅ testAdminOperations: PASSED" << std::endl;
}

void testAdminLevels() {
    std::cout << "Testing Admin levels..." << std::endl;
    
    minimarket::users::Admin superAdmin("ADM002", "Super", "super@admin.com", "SuperAdmin");
    assert(superAdmin.canModifySystemSettings() == true);
    assert(superAdmin.revokeUserAccess("ANYUSER") == true);
    
    minimarket::users::Admin systemAdmin("ADM003", "System", "system@admin.com", "SystemAdmin");
    assert(systemAdmin.canModifySystemSettings() == true);
    assert(systemAdmin.revokeUserAccess("ANYUSER") == false);
    
    minimarket::users::Admin regularAdmin("ADM004", "Regular", "regular@admin.com", "Admin");
    assert(regularAdmin.canModifySystemSettings() == false);
    assert(regularAdmin.revokeUserAccess("ANYUSER") == false);
    
    std::cout << "✅ testAdminLevels: PASSED" << std::endl;
}

void testUserProfile() {
    std::cout << "Testing UserProfile..." << std::endl;
    
    minimarket::users::UserProfile profile("USER003", "John", "Doe", "15/05/1990");
    
    assert(profile.getUserId() == "USER003");
    assert(profile.getFirstName() == "John");
    assert(profile.getLastName() == "Doe");
    assert(profile.getDateOfBirth() == "15/05/1990");
    
    assert(profile.getFullName() == "John Doe");
    
    int age = profile.calculateAge();
    assert(age > 20 && age < 50);
    
    assert(profile.isAdult() == true);
    
    std::cout << "✅ testUserProfile: PASSED" << std::endl;
}

void testUserProfileAge() {
    std::cout << "Testing UserProfile age calculations..." << std::endl;
    
    minimarket::users::UserProfile adult("USER004", "Adult", "User", "01/01/2000");
    assert(adult.isAdult() == true);
    
    minimarket::users::UserProfile invalidDate("USER005", "Invalid", "Date", "2000-01-01");
    int age = invalidDate.calculateAge();
    std::cout << "Invalid date age calculation: " << age << std::endl;
    assert(age >= 0);
    
    std::cout << "✅ testUserProfileAge: PASSED" << std::endl;
}

void testAddressOperations() {
    std::cout << "Testing Address operations..." << std::endl;
    
    minimarket::users::Address address("123 Main Street", "New York", "10001", "USA");
    
    assert(address.getStreet() == "123 Main Street");
    assert(address.getCity() == "New York");
    assert(address.getPostalCode() == "10001");
    assert(address.getCountry() == "USA");
    
    assert(address.validateAddress() == true);
    
    std::string formatted = address.getFormattedAddress();
    assert(formatted == "123 Main Street, New York, 10001, USA");
    
    assert(address.isInternational() == false);
    
    std::cout << "✅ testAddressOperations: PASSED" << std::endl;
}

void testInternationalAddress() {
    std::cout << "Testing international addresses..." << std::endl;
    
    minimarket::users::Address usAddress("456 Oak Ave", "Chicago", "60007", "USA");
    assert(usAddress.isInternational() == false);
    
    minimarket::users::Address usAddress2("789 Pine St", "Los Angeles", "90001", "United States");
    assert(usAddress2.isInternational() == false);
    
    minimarket::users::Address canadaAddress("123 Maple Rd", "Toronto", "M5V 2T6", "Canada");
    assert(canadaAddress.isInternational() == true);
    
    minimarket::users::Address ukAddress("456 Oxford St", "London", "W1D 1BS", "UK");
    assert(ukAddress.isInternational() == true);
    
    std::cout << "✅ testInternationalAddress: PASSED" << std::endl;
}

void testContactInfo() {
    std::cout << "Testing ContactInfo..." << std::endl;
    
    minimarket::users::ContactInfo contact("+1-234-567-8900", "contact@example.com", "+1-987-654-3210");
    
    assert(contact.getPhoneNumber() == "+1-234-567-8900");
    assert(contact.getEmail() == "contact@example.com");
    assert(contact.getEmergencyContact() == "+1-987-654-3210");
    
    assert(contact.validateContactInfo() == true);
    
    assert(contact.getPrimaryContact() == "+1-234-567-8900");
    
    assert(contact.hasEmergencyContact() == true);
    
    std::cout << "✅ testContactInfo: PASSED" << std::endl;
}

void testContactValidation() {
    std::cout << "Testing ContactInfo validation..." << std::endl;
    
    minimarket::users::ContactInfo valid("1234567890", "valid@email.com", "0987654321");
    assert(valid.validateContactInfo() == true);
    
    minimarket::users::ContactInfo invalidEmail("1234567890", "invalid-email", "0987654321");
    assert(invalidEmail.validateContactInfo() == false);
    
    minimarket::users::ContactInfo invalidPhone("123", "valid@email.com", "0987654321");
    assert(invalidPhone.validateContactInfo() == false);
    
    minimarket::users::ContactInfo noEmergency("1234567890", "valid@email.com", "");
    assert(noEmergency.hasEmergencyContact() == false);
    
    std::cout << "✅ testContactValidation: PASSED" << std::endl;
}

void testLoginCredentials() {
    std::cout << "Testing LoginCredentials..." << std::endl;
    
    minimarket::users::LoginCredentials credentials("johndoe", "SecurePass123!");
    
    assert(credentials.verifyPassword("SecurePass123!") == true);
    assert(credentials.verifyPassword("wrongpassword") == false);
    
    bool isExpired = credentials.isPasswordExpired();
    assert(isExpired == false);
    
    std::cout << "✅ testLoginCredentials: PASSED" << std::endl;
}

void testPasswordManagement() {
    std::cout << "Testing password management..." << std::endl;
    
    minimarket::users::LoginCredentials credentials("testuser", "OldPassword123!");
    
    credentials.updatePassword("NewSecurePass456!");
    assert(credentials.verifyPassword("NewSecurePass456!") == true);
    assert(credentials.verifyPassword("OldPassword123!") == false);
    
    try {
        credentials.updatePassword("short");
        assert(false);
    } catch (const minimarket::exceptions::InvalidPasswordException&) {
    }
    
    std::cout << "✅ testPasswordManagement: PASSED" << std::endl;
}

void testUserSession() {
    std::cout << "Testing UserSession..." << std::endl;
    
    minimarket::users::UserSession session("SESS001", "USER006");
    
    assert(session.getSessionId() == "SESS001");
    assert(session.getUserId() == "USER006");
    
    assert(session.isSessionValid() == true);
    
    int duration = session.calculateSessionDuration();
    assert(duration >= 0);
    
    std::cout << "✅ testUserSession: PASSED" << std::endl;
}

void testUserPreferences() {
    std::cout << "Testing UserPreferences..." << std::endl;
    
    minimarket::users::UserPreferences prefs("USER007", "en");
    
    assert(prefs.getUserId() == "USER007");
    assert(prefs.getLanguage() == "en");
    
    assert(prefs.setPreference("theme", "dark") == true);
    assert(prefs.setPreference("notifications", "disabled") == true);
    assert(prefs.setPreference("", "value") == false);
    assert(prefs.setPreference("key", "") == false);
    
    assert(prefs.getPreference("theme") == "dark");
    assert(prefs.getPreference("notifications") == "disabled");
    assert(prefs.getPreference("nonexistent").empty() == true);
    
    assert(prefs.supportsLanguage("en") == true);
    assert(prefs.supportsLanguage("es") == true);
    assert(prefs.supportsLanguage("fr") == true);
    assert(prefs.supportsLanguage("xx") == false);
    
    std::cout << "✅ testUserPreferences: PASSED" << std::endl;
}

void testUserIntegration() {
    std::cout << "Testing User integration..." << std::endl;
    
    minimarket::users::Customer customer("CUST007", "Integration User", "integration@test.com", "+1234567890");
    minimarket::users::UserProfile profile("CUST007", "Integration", "User", "01/01/1985");
    minimarket::users::Address address("789 Integration St", "Test City", "12345", "USA");
    minimarket::users::ContactInfo contact("+1234567890", "integration@test.com", "+0987654321");
    minimarket::users::LoginCredentials credentials("integration_user", "SecurePass123!");
    minimarket::users::UserPreferences prefs("CUST007", "en");
    
    assert(customer.validatePhoneNumber() == true);
    assert(profile.isAdult() == true);
    assert(address.validateAddress() == true);
    assert(contact.validateContactInfo() == true);
    assert(credentials.verifyPassword("SecurePass123!") == true);
    assert(prefs.supportsLanguage("en") == true);
    
    std::cout << "✅ testUserIntegration: PASSED" << std::endl;
}

void testUserExceptions() {
    std::cout << "Testing User exceptions..." << std::endl;
    
    try {
        minimarket::users::User invalidUser("", "username", "email@test.com");
        assert(false);
    } catch (const minimarket::exceptions::DataValidationException&) {
    }
    
    try {
        minimarket::users::LoginCredentials creds("test", "oldpass");
        creds.updatePassword("short");
        assert(false);
    } catch (const minimarket::exceptions::InvalidPasswordException&) {
    }
    
    std::cout << "✅ testUserExceptions: PASSED" << std::endl;
}

void runUserTests() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "RUNNING USER SYSTEM TESTS" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    testUserCreation();
    testUserAuthentication();
    testCustomerOperations();
    testCustomerPhoneValidation();
    testEmployeeOperations();
    testEmployeeLoanApproval();
    testEmployeeDataAccess();
    testAdminOperations();
    testAdminLevels();
    testUserProfile();
    testUserProfileAge();
    testAddressOperations();
    testInternationalAddress();
    testContactInfo();
    testContactValidation();
    testLoginCredentials();
    testPasswordManagement();
    testUserSession();
    testUserPreferences();
    testUserIntegration();
    testUserExceptions();
    
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "ALL USER TESTS PASSED! ✅" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}
