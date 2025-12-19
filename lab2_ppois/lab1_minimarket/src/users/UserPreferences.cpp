#include "../../include/users/UserPreferences.hpp"
#include <algorithm>

namespace minimarket {
namespace users {

UserPreferences::UserPreferences(const std::string& uid, const std::string& lang)
    : userId(uid), language(lang) {
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
