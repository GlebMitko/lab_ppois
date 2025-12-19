#include "../../include/users/Address.hpp"

namespace minimarket {
namespace users {

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

} // namespace users
} // namespace minimarket
