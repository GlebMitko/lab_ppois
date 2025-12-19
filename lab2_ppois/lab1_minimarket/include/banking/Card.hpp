#ifndef MINIMARKET_BANKING_CARD_HPP
#define MINIMARKET_BANKING_CARD_HPP

#include <string>

namespace minimarket {
namespace banking {

class Card {
public:
    Card(const std::string& number, const std::string& name, const std::string& expiry);
    bool verifyPin(const std::string& pin);
    bool processPayment(double amount) const;
    void blockCard();

    const std::string& getCardNumber() const { return cardNumber; }
    const std::string& getHolderName() const { return holderName; }
    const std::string& getExpiryDate() const { return expiryDate; }

private:
    std::string cardNumber;
    std::string holderName;
    std::string expiryDate;
    int pinAttempts;
};

} // namespace banking
} // namespace minimarket

#endif
