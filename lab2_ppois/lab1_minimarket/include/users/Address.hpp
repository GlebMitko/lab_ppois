#ifndef MINIMARKET_USERS_ADDRESS_HPP
#define MINIMARKET_USERS_ADDRESS_HPP

#include <string>

namespace minimarket {
namespace users {

class Address {
public:
    Address(const std::string& st, const std::string& ct, const std::string& postal, const std::string& cntry);
    bool validateAddress() const;
    std::string getFormattedAddress() const;
    bool isInternational() const;

    const std::string& getStreet() const { return street; }
    const std::string& getCity() const { return city; }
    const std::string& getPostalCode() const { return postalCode; }
    const std::string& getCountry() const { return country; }

private:
    std::string street;
    std::string city;
    std::string postalCode;
    std::string country;
};

} // namespace users
} // namespace minimarket

#endif
