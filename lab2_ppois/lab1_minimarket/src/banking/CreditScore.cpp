#include "../../include/banking/CreditScore.hpp"

namespace minimarket {
namespace banking {

CreditScore::CreditScore(int initialScore) : score(initialScore), lastUpdate(std::time(nullptr)) {}

bool CreditScore::qualifyForLoan(double amount) const {
    return score >= 650 && amount <= score * 100;
}

void CreditScore::updateScore(int newScore) {
    score = newScore;
    lastUpdate = std::time(nullptr);
}

} // namespace banking
} // namespace minimarket
