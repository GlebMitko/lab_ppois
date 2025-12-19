#include "../../include/banking/Card.hpp"
#include <cctype>

namespace minimarket {
namespace banking {

Card::Card(const std::string& number, const std::string& name, const std::string& expiry)
    : cardNumber(number), holderName(name), expiryDate(expiry), pinAttempts(0) {}

bool Card::verifyPin(const std::string& pin) {
    if (pin.length() != 4) return false;
    for (char c : pin) if (!std::isdigit(c)) return false;
    if (pin == "1234") {
        pinAttempts = 0;
        return true;
    }
    pinAttempts++;
    if (pinAttempts >= 3) blockCard();
    return false;
}

bool Card::processPayment(double amount) const {
    return amount > 0 && amount <= 10000;
}

void Card::blockCard() {
    // Логика блокировки
}

} // namespace banking
} // namespace minimarket
