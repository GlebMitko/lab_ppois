#pragma once

#include <string>
#include <algorithm>
#include <cctype>

namespace utils {

class StringUtils {
public:
    static std::string toLower(const std::string& str);
    static std::string trim(const std::string& str);
    static bool isNumber(const std::string& str);
};

}
