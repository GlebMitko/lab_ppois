#ifndef MINIMARKET_BANKING_CREDITSCORE_HPP
#define MINIMARKET_BANKING_CREDITSCORE_HPP

#include <ctime>

namespace minimarket {
namespace banking {

class CreditScore {
public:
    CreditScore(int initialScore);
    bool qualifyForLoan(double amount) const;
    void updateScore(int newScore);
    int getScore() const { return score; }
    std::time_t getLastUpdate() const { return lastUpdate; }

private:
    int score;
    std::time_t lastUpdate;
};

} // namespace banking
} // namespace minimarket

#endif
