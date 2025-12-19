#ifndef MINIMARKET_USERS_USERPREFERENCES_HPP
#define MINIMARKET_USERS_USERPREFERENCES_HPP

#include <string>
#include <map>
#include <vector>

namespace minimarket {
namespace users {

class UserPreferences {
public:
    UserPreferences(const std::string& uid, const std::string& lang);
    bool setPreference(const std::string& key, const std::string& value);
    std::string getPreference(const std::string& key) const;
    bool supportsLanguage(const std::string& lang) const;

    const std::string& getUserId() const { return userId; }
    const std::string& getLanguage() const { return language; }

private:
    std::string userId;
    std::string language;
    std::map<std::string, std::string> preferences;
};

} // namespace users
} // namespace minimarket

#endif
