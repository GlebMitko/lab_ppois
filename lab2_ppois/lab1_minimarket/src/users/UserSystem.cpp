#include "../../include/users/UserSystem.hpp"
#include "../../include/utils/Exceptions.hpp"
#include <ctime>
#include <algorithm>
#include <cmath>

namespace minimarket {
namespace users {

// 1. User implementation
User::User(const std::string& id, const std::string& name, const std::string& userEmail)
    : userId(id), username(name), email(userEmail) {
    if (id.empty() || name.empty()) {
        throw exceptions::DataValidationException("User ID and name cannot be empty");
    }
}

bool User::authenticate(const std::string& password) const {
    return password.length() >= 8 &&
           password.find_first_of("0123456789") != std::string::npos &&
           password.find_first_of("!@#$%") != std::string::npos;
}

std::string User::getUserRole() const {
    return "BaseUser";
}

bool User::updateEmail(const std::string& newEmail) {
    if (newEmail.empty() || newEmail.find('@') == std::string::npos) return false;
    email = newEmail;
    return true;
}

// 2. Customer implementation
Customer::Customer(const std::string& id, const std::string& name,
                   const std::string& email, const std::string& phone)
    : User(id, name, email), customerId(id), phoneNumber(phone), registrationDate(std::time(nullptr)) {}

bool Customer::validatePhoneNumber() const {
    return phoneNumber.length() >= 10 &&
           phoneNumber.find_first_not_of("0123456789+- ()") == std::string::npos;
}

int Customer::calculateLoyaltyYears() const {
    std::time_t now = std::time(nullptr);
    double secondsDiff = std::difftime(now, registrationDate);
    return static_cast<int>(secondsDiff / (365.25 * 24 * 60 * 60));
}

bool Customer::canApplyForPremium() const {
    return calculateLoyaltyYears() >= 2 && validatePhoneNumber();
}

// 3. Employee implementation
Employee::Employee(const std::string& id, const std::string& name,
                   const std::string& email, const std::string& dept, double sal)
    : User(id, name, email), employeeId(id), department(dept), salary(sal) {}

bool Employee::approveLoanApplication(double amount) const {
    return department == "Loans" && salary > 30000 && amount <= 100000;
}

double Employee::calculateAnnualBonus() const {
    return salary * 0.15; // 15% годовой бонус
}

bool Employee::canAccessSensitiveData() const {
    return department == "HR" || department == "Finance" || department == "IT";
}

// 4. Admin implementation
Admin::Admin(const std::string& id, const std::string& name,
             const std::string& email, const std::string& level)
    : User(id, name, email), adminLevel(level) {}

bool Admin::grantPermissions(const std::string& permission) {
    if (permission.empty()) return false;
    permissions.push_back(permission);
    return true;
}

bool Admin::revokeUserAccess(const std::string& targetUserId) {
    return !targetUserId.empty() && adminLevel == "SuperAdmin";
}

bool Admin::canModifySystemSettings() const {
    return adminLevel == "SuperAdmin" || adminLevel == "SystemAdmin";
}

// 5. UserProfile implementation
UserProfile::UserProfile(const std::string& id, const std::string& first,
                         const std::string& last, const std::string& dob)
    : userId(id), firstName(first), lastName(last), dateOfBirth(dob) {}

int UserProfile::calculateAge() const {
    // Упрощенный расчет возраста
    if (dateOfBirth.length() != 10) return 0; // DD/MM/YYYY
    int birthYear = std::stoi(dateOfBirth.substr(6, 4));
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    int currentYear = localTime->tm_year + 1900;
    return currentYear - birthYear;
}

std::string UserProfile::getFullName() const {
    return firstName + " " + lastName;
}

bool UserProfile::isAdult() const {
    return calculateAge() >= 18;
}

// 6. Address implementation
Address::Address(const std::string& st, const std::string& ct,
                 const std::string& postal, const std::string& cntry)
    : street(st), city(ct), postalCode(postal), country(cntry) {}

bool Address::validateAddress() const {
    return !street.empty() && !city.empty() &&
           !postalCode.empty() && !country.empty();
}

std::string Address::getFormattedAddress() const {
    return street + ", " + city + ", " + postalCode + ", " + country;
}

bool Address::isInternational() const {
    return country != "USA" && country != "United States";
}

// 7. ContactInfo implementation
ContactInfo::ContactInfo(const std::string& phone, const std::string& mail,
                         const std::string& emergency)
    : phoneNumber(phone), email(mail), emergencyContact(emergency) {}

bool ContactInfo::validateContactInfo() const {
    bool validEmail = !email.empty() && email.find('@') != std::string::npos;
    bool validPhone = !phoneNumber.empty() && phoneNumber.length() >= 10;
    return validEmail && validPhone;
}

std::string ContactInfo::getPrimaryContact() const {
    return !phoneNumber.empty() ? phoneNumber : email;
}

bool ContactInfo::hasEmergencyContact() const {
    return !emergencyContact.empty();
}

// 8. LoginCredentials implementation
LoginCredentials::LoginCredentials(const std::string& user, const std::string& password)
    : username(user), lastLogin(std::time(nullptr)) {
    // Упрощенное "хэширование" - в реальной системе используйте bcrypt/scrypt
    passwordHash = std::to_string(std::hash<std::string>{}(password));
}

bool LoginCredentials::verifyPassword(const std::string& inputPassword) const {
    std::string inputHash = std::to_string(std::hash<std::string>{}(inputPassword));
    return inputHash == passwordHash;
}

void LoginCredentials::updatePassword(const std::string& newPassword) {
    if (newPassword.length() < 8) {
        throw exceptions::InvalidPasswordException("Password must be at least 8 characters");
    }
    passwordHash = std::to_string(std::hash<std::string>{}(newPassword));
    lastLogin = std::time(nullptr);
}

bool LoginCredentials::isPasswordExpired() const {
    std::time_t now = std::time(nullptr);
    double daysDiff = std::difftime(now, lastLogin) / (60 * 60 * 24);
    return daysDiff > 90; // Пароль истекает через 90 дней
}

// 9. UserSession implementation
UserSession::UserSession(const std::string& sessId, const std::string& uid)
    : sessionId(sessId), userId(uid), startTime(std::time(nullptr)), lastActivity(std::time(nullptr)) {}

bool UserSession::isSessionValid() const {
    std::time_t now = std::time(nullptr);
    double minutesDiff = std::difftime(now, lastActivity) / 60;
    return minutesDiff < 30; // Сессия действительна 30 минут
}

void UserSession::refreshSession() {
    lastActivity = std::time(nullptr);
}

int UserSession::calculateSessionDuration() const {
    return static_cast<int>(std::difftime(lastActivity, startTime) / 60); // в минутах
}

// 10. UserPreferences implementation
UserPreferences::UserPreferences(const std::string& uid, const std::string& lang)
    : userId(uid), language(lang) {
    // Настройки по умолчанию
    preferences["theme"] = "light";
    preferences["notifications"] = "enabled";
    preferences["currency"] = "USD";
}

bool UserPreferences::setPreference(const std::string& key, const std::string& value) {
    if (key.empty() || value.empty()) return false;
    preferences[key] = value;
    return true;
}

std::string UserPreferences::getPreference(const std::string& key) const {
    auto it = preferences.find(key);
    return it != preferences.end() ? it->second : "";
}

bool UserPreferences::supportsLanguage(const std::string& lang) const {
    std::vector<std::string> supportedLanguages = {"en", "es", "fr", "de", "ru"};
    return std::find(supportedLanguages.begin(), supportedLanguages.end(), lang) != supportedLanguages.end();
}

} // namespace users
} // namespace minimarket
