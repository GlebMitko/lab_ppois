#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <ctime>
#include "../utils/Exceptions.hpp"

namespace minimarket {
namespace users {

// 1. Базовый класс пользователя
class User {
private:
    std::string userId;
    std::string username;
    std::string email;
public:
    User(const std::string& id, const std::string& name, const std::string& userEmail);
    
    // Добавляем геттеры
    std::string getUserId() const { return userId; }
    std::string getUsername() const { return username; }
    std::string getEmail() const { return email; }
    
    virtual bool authenticate(const std::string& password) const;
    virtual std::string getUserRole() const;
    bool updateEmail(const std::string& newEmail);
};

// 2. Клиент банка
class Customer : public User {
private:
    std::string customerId;
    std::string phoneNumber;
    std::time_t registrationDate;
public:
    Customer(const std::string& id, const std::string& name,
             const std::string& email, const std::string& phone);
    
    // Добавляем геттеры
    std::string getCustomerId() const { return customerId; }
    std::string getPhoneNumber() const { return phoneNumber; }
    
    bool validatePhoneNumber() const;
    int calculateLoyaltyYears() const;
    bool canApplyForPremium() const;
};

// 3. Сотрудник банка
class Employee : public User {
private:
    std::string employeeId;
    std::string department;
    double salary;
public:
    Employee(const std::string& id, const std::string& name,
             const std::string& email, const std::string& dept, double sal);
    
    // Добавляем геттеры
    std::string getEmployeeId() const { return employeeId; }
    std::string getDepartment() const { return department; }
    double getSalary() const { return salary; }
    
    bool approveLoanApplication(double amount) const;
    double calculateAnnualBonus() const;
    bool canAccessSensitiveData() const;
};

// 4. Администратор системы
class Admin : public User {
private:
    std::string adminLevel;
    std::vector<std::string> permissions;
public:
    Admin(const std::string& id, const std::string& name,
          const std::string& email, const std::string& level);
    
    // Добавляем геттеры
    std::string getAdminLevel() const { return adminLevel; }
    
    bool grantPermissions(const std::string& permission);
    bool revokeUserAccess(const std::string& targetUserId);
    bool canModifySystemSettings() const;
};

// 5. Профиль пользователя
class UserProfile {
private:
    std::string userId;
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
public:
    UserProfile(const std::string& id, const std::string& first,
                const std::string& last, const std::string& dob);
    
    // Добавляем геттеры
    std::string getUserId() const { return userId; }
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getDateOfBirth() const { return dateOfBirth; }
    
    int calculateAge() const;
    std::string getFullName() const;
    bool isAdult() const;
};

// 6. Адрес пользователя
class Address {
private:
    std::string street;
    std::string city;
    std::string postalCode;
    std::string country;
public:
    Address(const std::string& st, const std::string& ct,
            const std::string& postal, const std::string& cntry);
    
    // Добавляем геттеры
    std::string getStreet() const { return street; }
    std::string getCity() const { return city; }
    std::string getPostalCode() const { return postalCode; }
    std::string getCountry() const { return country; }
    
    bool validateAddress() const;
    std::string getFormattedAddress() const;
    bool isInternational() const;
};

// 7. Контактная информация
class ContactInfo {
private:
    std::string phoneNumber;
    std::string email;
    std::string emergencyContact;
public:
    ContactInfo(const std::string& phone, const std::string& mail,
                const std::string& emergency);
    
    // Добавляем геттеры
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getEmail() const { return email; }
    std::string getEmergencyContact() const { return emergencyContact; }
    
    bool validateContactInfo() const;
    std::string getPrimaryContact() const;
    bool hasEmergencyContact() const;
};

// 8. Учетные данные для входа
class LoginCredentials {
private:
    std::string username;
    std::string passwordHash;
    std::time_t lastLogin;
public:
    LoginCredentials(const std::string& user, const std::string& password);
    
    // Добавляем геттеры
    std::string getUsername() const { return username; }
    std::time_t getLastLogin() const { return lastLogin; }
    
    bool verifyPassword(const std::string& inputPassword) const;
    void updatePassword(const std::string& newPassword);
    bool isPasswordExpired() const;
};

// 9. Сессия пользователя
class UserSession {
private:
    std::string sessionId;
    std::string userId;
    std::time_t startTime;
    std::time_t lastActivity;
public:
    UserSession(const std::string& sessId, const std::string& uid);
    
    // Добавляем геттеры
    std::string getSessionId() const { return sessionId; }
    std::string getUserId() const { return userId; }
    std::time_t getStartTime() const { return startTime; }
    std::time_t getLastActivity() const { return lastActivity; }
    
    bool isSessionValid() const;
    void refreshSession();
    int calculateSessionDuration() const;
};

// 10. Настройки пользователя
class UserPreferences {
private:
    std::string userId;
    std::map<std::string, std::string> preferences;
    std::string language;
public:
    UserPreferences(const std::string& uid, const std::string& lang = "en");
    
    // Добавляем геттеры
    std::string getUserId() const { return userId; }
    std::string getLanguage() const { return language; }
    
    bool setPreference(const std::string& key, const std::string& value);
    std::string getPreference(const std::string& key) const;
    bool supportsLanguage(const std::string& lang) const;
};

} // namespace users
} // namespace minimarket
