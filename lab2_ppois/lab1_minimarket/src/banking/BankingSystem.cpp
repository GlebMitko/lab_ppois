#include "../../include/banking/BankingSystem.hpp"
#include "../../include/utils/Exceptions.hpp"
#include <cmath>
#include <algorithm>
#include <random>

namespace minimarket {
namespace banking {

// 1. Balance implementation
Balance::Balance(double amount, const std::string& currency)
    : availableAmount(amount), reservedAmount(0.0), currencyCode(currency) {
    if (amount < 0) throw exceptions::InvalidOperationException("Balance cannot be negative");
}

bool Balance::withdraw(double amount) {
    if (amount <= 0 || amount > availableAmount) return false;
    availableAmount -= amount;
    return true;
}

void Balance::reserveFunds(double amount) {
    if (amount <= 0 || amount > availableAmount) {
        throw exceptions::InsufficientFundsException("Cannot reserve funds");
    }
    availableAmount -= amount;
    reservedAmount += amount;
}

double Balance::calculateTotal() const {
    return availableAmount + reservedAmount;
}

// 2. Transaction implementation
Transaction::Transaction(const std::string& id, double amt, const std::string& tp)
    : transactionId(id), amount(amt), type(tp), timestamp(std::time(nullptr)) {
    if (amt <= 0) throw exceptions::InvalidOperationException("Transaction amount must be positive");
}

bool Transaction::validateTransaction() const {
    return !transactionId.empty() && amount > 0 && !type.empty();
}

std::string Transaction::generateReceipt() const {
    return "Receipt for " + std::to_string(amount) + " - " + type + " - ID: " + transactionId;
}

// 3. Account implementation
Account::Account(const std::string& number, const std::string& name)
    : accountNumber(number), holderName(name), balance(std::make_shared<Balance>(0.0)) {}

bool Account::transferMoney(double amount, Account& target) {
    if (!balance->withdraw(amount)) return false;
    // В реальной системе здесь был бы вызов метода target.deposit()
    return true;
}

bool Account::applyOverdraft(double limit) {
    return limit > 0; // Упрощенная логика
}

double Account::calculateInterest() const {
    return balance->calculateTotal() * 0.02; // 2% годовых
}

double Account::getAvailableBalance() const {
    return balance ? balance->getAvailableAmount() : 0.0;
}

// 4. Card implementation
Card::Card(const std::string& number, const std::string& name, const std::string& expiry)
    : cardNumber(number), holderName(name), expiryDate(expiry), pinAttempts(0) {}

bool Card::verifyPin(const std::string& pin) {
    if (pin.length() != 4) return false;
    for (char c : pin) if (!isdigit(c)) return false;
    
    if (pin == "1234") { // Упрощенная проверка
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
    // Карта блокируется при 3 неудачных попытках PIN
}

// 5. Bank implementation
// Bank implementation
Bank::Bank(const std::string& code, const std::string& name)
    : bankCode(code), bankName(name) {}

std::string Bank::getBankCode() const {
    return bankCode;
}

std::string Bank::getBankName() const {
    return bankName;
}

bool Bank::addAccount(const std::shared_ptr<Account>& account) {
    if (!account) return false;
    accounts.push_back(account);
    return true;
}

bool Bank::openAccount(const std::string& holderName) {
    if (holderName.empty()) return false;
    std::string accountNumber = "ACC" + std::to_string(accounts.size() + 1);
    accounts.push_back(std::make_shared<Account>(accountNumber, holderName));
    return true;
}

bool Bank::closeAccount(const std::string& accountNumber) {
    auto it = std::remove_if(accounts.begin(), accounts.end(),
        [&](const auto& acc) { return acc->getAccountNumber() == accountNumber; });
    bool found = it != accounts.end();
    accounts.erase(it, accounts.end());
    return found;
}

double Bank::calculateTotalAssets() const {
    double total = 0.0;
    for (const auto& account : accounts) {
        total += account->getAvailableBalance();
    }
    return total;
}

size_t Bank::getTotalAccountsCount() const {
    return accounts.size();
}

// 6. CreditCard implementation

bool CreditCard::useCredit(double amount) {
    if (amount <= 0 || usedCredit + amount > creditLimit) return false;
    usedCredit += amount;
    return true;
}

double CreditCard::calculateAvailableCredit() const {
    return creditLimit - usedCredit;
}

// 7. Loan implementation
Loan::Loan(double principal, double rate, int term)
    : principalAmount(principal), interestRate(rate), termMonths(term) {}

double Loan::calculateMonthlyPayment() const {
    double monthlyRate = interestRate / 100 / 12;
    return principalAmount * monthlyRate * pow(1 + monthlyRate, termMonths) /
           (pow(1 + monthlyRate, termMonths) - 1);
}

double Loan::calculateTotalInterest() const {
    return calculateMonthlyPayment() * termMonths - principalAmount;
}

// 8. Mortgage implementation
Mortgage::Mortgage(double principal, double rate, int term,
                   const std::string& address, double down)
    : Loan(principal, rate, term), propertyAddress(address), downPayment(down) {}

bool Mortgage::validateDownPayment() const {
    return downPayment >= getPrincipalAmount() * 0.2; // Минимум 20%
}

double Mortgage::calculateLTV() const {
    return (getPrincipalAmount() - downPayment) / getPrincipalAmount() * 100;
}

// 9. InvestmentAccount implementation
InvestmentAccount::InvestmentAccount(const std::string& number, const std::string& name,
                                     const std::string& type, double risk)
    : Account(number, name), investmentType(type), riskLevel(risk) {}

double InvestmentAccount::calculateExpectedReturn() const {
    return calculateInterest() * (1.0 + riskLevel / 10.0);
}

bool InvestmentAccount::rebalancePortfolio() {
    return riskLevel > 0.5; // Упрощенная логика ребалансировки
}

// 10. CreditScore implementation
CreditScore::CreditScore(int initialScore) : score(initialScore), lastUpdate(std::time(nullptr)) {}

bool CreditScore::qualifyForLoan(double amount) const {
    return score >= 650 && amount <= score * 100; // Упрощенные критерии
}

void CreditScore::updateScore(int newScore) {
    score = newScore;
    lastUpdate = std::time(nullptr);
}

// 11. ATM implementation
ATM::ATM(const std::string& id, const std::string& loc, double cash)
    : atmId(id), location(loc), cashBalance(cash) {}

bool ATM::dispenseCash(double amount) {
    if (amount <= 0 || amount > cashBalance || amount > 1000) return false;
    cashBalance -= amount;
    return true;
}

bool ATM::processDeposit(double amount) {
    if (amount <= 0) return false;
    cashBalance += amount;
    return true;
}

// 12. Branch implementation


// 13. BankTransfer implementation
BankTransfer::BankTransfer(const std::string& id, double amt,
                           const std::string& from, const std::string& to)
    : transferId(id), amount(amt), fromAccount(from), toAccount(to) {}

bool BankTransfer::executeTransfer() {
    return validateAccounts() && amount > 0 && amount <= 50000;
}

bool BankTransfer::validateAccounts() const {
    return !fromAccount.empty() && !toAccount.empty() && fromAccount != toAccount;
}

// 14. PaymentProcessor implementation
PaymentProcessor::PaymentProcessor(const std::string& id, double fee)
    : processorId(id), transactionFee(fee) {}

bool PaymentProcessor::processCardPayment(const Card& card, double amount) const {
    return card.processPayment(amount) && amount > 0;
}

double PaymentProcessor::calculateFee(double amount) const {
    return amount * transactionFee;
}

// 15. BankStatement implementation
BankStatement::BankStatement(const std::string& accNumber, std::time_t start, std::time_t end)
    : accountNumber(accNumber), periodStart(start), periodEnd(end) {}

double BankStatement::calculateEndingBalance() const {
    double balance = 0.0;
    for (const auto& transaction : transactions) {
        balance += transaction.getAmount(); // Упрощенный расчет
    }
    return balance;
}

void BankStatement::generatePDFReport() const {
    // Логика генерации отчета
}

// 16. FraudDetector implementation
FraudDetector::FraudDetector(double threshold) : fraudThreshold(threshold) {}

bool FraudDetector::detectFraud(const Transaction& transaction) {
    return transaction.getAmount() > fraudThreshold;
}

void FraudDetector::addSuspiciousPattern(const std::string& pattern) {
    suspiciousPatterns.push_back(pattern);
}

// 17. CurrencyConverter implementation
CurrencyConverter::CurrencyConverter() {
    exchangeRates = {{"USD", 1.0}, {"EUR", 0.85}, {"GBP", 0.75}};
}

double CurrencyConverter::convertAmount(double amount, const std::string& from,
                                       const std::string& to) const {
    auto fromIt = exchangeRates.find(from);
    auto toIt = exchangeRates.find(to);
    if (fromIt == exchangeRates.end() || toIt == exchangeRates.end()) return 0.0;
    return amount * toIt->second / fromIt->second;
}

void CurrencyConverter::updateExchangeRate(const std::string& currency, double rate) {
    exchangeRates[currency] = rate;
}

// 18. InterestCalculator implementation
InterestCalculator::InterestCalculator(double rate) : baseRate(rate) {}

double InterestCalculator::calculateCompoundInterest(double principal, int years) const {
    return principal * pow(1 + baseRate/100, years) - principal;
}

double InterestCalculator::calculateSimpleInterest(double principal, int years) const {
    return principal * baseRate / 100 * years;
}

// 19. TaxCalculator implementation
TaxCalculator::TaxCalculator(double rate) : taxRate(rate) {}

double TaxCalculator::calculateTax(double income) const {
    return income * taxRate / 100;
}

double TaxCalculator::calculateDeductions(double income) const {
    return std::min(income * 0.1, 5000.0); // Упрощенные вычеты
}

// 20. RiskAssessor implementation
RiskAssessor::RiskAssessor(double threshold) : riskThreshold(threshold) {}

double RiskAssessor::assessInvestmentRisk(double volatility, double returnRate) const {
    return volatility / returnRate; // Упрощенная формула риска
}

bool RiskAssessor::approveLoan(const CreditScore& score, double amount) const {
    return score.qualifyForLoan(amount) && amount <= riskThreshold;
}

// 21. CustomerService implementation
CustomerService::CustomerService(const std::string& dept, int agents)
    : department(dept), availableAgents(agents) {}

bool CustomerService::handleComplaint(const std::string& complaint) {
    return !complaint.empty() && availableAgents > 0;
}

int CustomerService::estimateWaitTime(int queueLength) const {
    return queueLength * 5; // 5 минут на клиента
}

// 22. SecuritySystem implementation
SecuritySystem::SecuritySystem(int level) : securityLevel(level) {}

bool SecuritySystem::authenticateUser(const std::string& credentials) {
    return credentials.length() >= 8 && securityLevel >= 2;
}

void SecuritySystem::logSecurityEvent(const std::string& event) {
    accessLogs.push_back(event);
}

// 23. AuditTrail implementation
AuditTrail::AuditTrail() {}

void AuditTrail::recordTransaction(const Transaction& transaction) {
    auditRecords.push_back(transaction.generateReceipt());
}

bool AuditTrail::verifyCompliance() const {
    return auditRecords.size() <= 1000; // Упрощенная проверка
}

// 24. NotificationService implementation
NotificationService::NotificationService() {
    notificationChannels = {"SMS", "Email", "Push"};
}

bool NotificationService::sendAlert(const std::string& message, const std::string& channel) {
    return !message.empty() && std::find(notificationChannels.begin(),
           notificationChannels.end(), channel) != notificationChannels.end();
}

void NotificationService::scheduleReminder(const std::string& reminder, std::time_t time) {
    // Логика планирования напоминания
}

// 25. ReportGenerator implementation
ReportGenerator::ReportGenerator(const std::string& format) : reportFormat(format) {}

std::string ReportGenerator::generateFinancialReport(const Bank& bank) const {
    return "Financial Report: Total Assets = " + std::to_string(bank.calculateTotalAssets());
}

std::string ReportGenerator::generateRiskReport(const RiskAssessor& assessor) const {
    return "Risk Report: Threshold = " + std::to_string(/*assessor.getThreshold()*/ 1000);
}

} // namespace banking
} // namespace minimarket
