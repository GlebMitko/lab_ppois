#pragma once
#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <unordered_map>
#include "../utils/Exceptions.hpp"

namespace minimarket {
namespace banking {

// 1. Базовые классы (5 классов)
class Balance {
private:
    double availableAmount;
    double reservedAmount;
    std::string currencyCode;
public:
    Balance(double amount, const std::string& currency = "USD");
    double getAvailableAmount() const { return availableAmount; } // ← ДОБАВИТЬ
    double getReservedAmount() const { return reservedAmount; }
    bool withdraw(double amount);                    // Уникальное поведение 1
    void reserveFunds(double amount);               // Уникальное поведение 2
    double calculateTotal() const;                  // Уникальное поведение 3
};

class Transaction {
private:
    std::string transactionId;
    double amount;
    std::string type;
    std::time_t timestamp;
public:
    Transaction(const std::string& id, double amt, const std::string& tp);
    double getAmount() const { return amount; }
    bool validateTransaction() const;               // Уникальное поведение 4
    std::string generateReceipt() const;            // Уникальное поведение 5
};

class Account {
private:
    std::string accountNumber;
    std::string holderName;
    std::shared_ptr<Balance> balance;
public:
    Account(const std::string& number, const std::string& name);
    
    std::string getAccountNumber() const { return accountNumber; }
    std::string getAccountHolderName() const { return holderName; }
    double getAvailableBalance() const;
    
    bool transferMoney(double amount, Account& target);
    bool applyOverdraft(double limit);
    double calculateInterest() const;
};

class Card {
private:
    std::string cardNumber;
    std::string holderName;
    std::string expiryDate;
    int pinAttempts;
public:
    Card(const std::string& number, const std::string& name, const std::string& expiry);
    
    std::string getCardNumber() const { return cardNumber; }
    std::string getCardHolderName() const { return holderName; }
    std::string getExpiryDate() const { return expiryDate; }
    
    bool verifyPin(const std::string& pin);
    bool processPayment(double amount) const;
    void blockCard();
};

class Bank {
private:
    std::string bankCode;
    std::string bankName;
    std::vector<std::shared_ptr<Account>> accounts;
public:
    Bank(const std::string& code, const std::string& name);
    
    std::string getBankCode() const;
    std::string getBankName() const;
    bool addAccount(const std::shared_ptr<Account>& account);
    bool openAccount(const std::string& holderName);
    bool closeAccount(const std::string& accountNumber);
    double calculateTotalAssets() const;
    size_t getTotalAccountsCount() const;
};

// 2. Кредитные продукты (5 классов)
class CreditCard : public Card {
private:
    double creditLimit;
    double usedCredit;
    double interestRate;
public:
    CreditCard(const std::string& number, const std::string& name,
               const std::string& expiry, double limit, double interest)
        : Card(number, name, expiry), creditLimit(limit), usedCredit(0.0), interestRate(interest) {}
    
    double getCreditLimit() const { return creditLimit; }
    double getUsedCredit() const { return usedCredit; }
    double calculateAvailableCredit() const;
    bool useCredit(double amount);
};

class Loan {
private:
    double principalAmount;
    double interestRate;
    int termMonths;
public:
    Loan(double principal, double rate, int term);
    double getPrincipalAmount() const { return principalAmount; }
    double calculateMonthlyPayment() const;         // Уникальное поведение 17
    double calculateTotalInterest() const;          // Уникальное поведение 18
};

class Mortgage : public Loan {
private:
    std::string propertyAddress;
    double downPayment;
public:
    Mortgage(double principal, double rate, int term,
             const std::string& address, double down);
    bool validateDownPayment() const;               // Уникальное поведение 19
    double calculateLTV() const;                    // Уникальное поведение 20
};

class InvestmentAccount : public Account {
private:
    std::string investmentType;
    double riskLevel;
public:
    InvestmentAccount(const std::string& number, const std::string& name,
                      const std::string& type, double risk);
    double calculateExpectedReturn() const;         // Уникальное поведение 21
    bool rebalancePortfolio();                      // Уникальное поведение 22
};

class CreditScore {
private:
    int score;
    std::time_t lastUpdate;
public:
    CreditScore(int initialScore);
    bool qualifyForLoan(double amount) const;       // Уникальное поведение 23
    void updateScore(int newScore);                 // Уникальное поведение 24
};

// 3. Операционные классы (5 классов)
class ATM {
private:
    std::string atmId;
    std::string location;
    double cashBalance;
public:
    ATM(const std::string& id, const std::string& loc, double cash);
    bool dispenseCash(double amount);               // Уникальное поведение 25
    bool processDeposit(double amount);             // Уникальное поведение 26
};

class Branch {
private:
    std::string branchCode;
    std::string address;
public:
    Branch(const std::string& code, const std::string& addr)
        : branchCode(code), address(addr) {}
    
    std::string getBranchCode() const { return branchCode; }
    std::string getAddress() const { return address; }
    
    bool addEmployee(const std::string& employeeId) { return !employeeId.empty(); } // Упрощенная версия
    int calculateStaffRequirements() const { return 5; } // Уникальное поведение 28
};

class BankTransfer {
private:
    std::string transferId;
    double amount;
    std::string fromAccount;
    std::string toAccount;
public:
    BankTransfer(const std::string& id, double amt,
                 const std::string& from, const std::string& to);
    bool executeTransfer();                         // Уникальное поведение 29
    bool validateAccounts() const;                  // Уникальное поведение 30
};

class PaymentProcessor {
private:
    std::string processorId;
    double transactionFee;
public:
    PaymentProcessor(const std::string& id, double fee);
    bool processCardPayment(const Card& card, double amount) const; // Уникальное поведение 31
    double calculateFee(double amount) const;       // Уникальное поведение 32
};

class BankStatement {
private:
    std::string accountNumber;
    std::vector<Transaction> transactions;
    std::time_t periodStart;
    std::time_t periodEnd;
public:
    BankStatement(const std::string& accNumber, std::time_t start, std::time_t end);
    double calculateEndingBalance() const;          // Уникальное поведение 33
    void generatePDFReport() const;                 // Уникальное поведение 34
};

// 4. Специализированные сервисы (5 классов)
class FraudDetector {
private:
    std::vector<std::string> suspiciousPatterns;
    double fraudThreshold;
public:
    FraudDetector(double threshold);
    bool detectFraud(const Transaction& transaction); // Уникальное поведение 35
    void addSuspiciousPattern(const std::string& pattern); // Уникальное поведение 36
};

class CurrencyConverter {
private:
    std::unordered_map<std::string, double> exchangeRates;
public:
    CurrencyConverter();
    double convertAmount(double amount, const std::string& from,
                        const std::string& to) const; // Уникальное поведение 37
    void updateExchangeRate(const std::string& currency, double rate); // Уникальное поведение 38
};

class InterestCalculator {
private:
    double baseRate;
public:
    InterestCalculator(double rate);
    double calculateCompoundInterest(double principal, int years) const; // Уникальное поведение 39
    double calculateSimpleInterest(double principal, int years) const; // Уникальное поведение 40
};

class TaxCalculator {
private:
    double taxRate;
public:
    TaxCalculator(double rate);
    double calculateTax(double income) const;       // Уникальное поведение 41
    double calculateDeductions(double income) const; // Уникальное поведение 42
};

class RiskAssessor {
private:
    double riskThreshold;
public:
    RiskAssessor(double threshold);
    double assessInvestmentRisk(double volatility, double returnRate) const; // Уникальное поведение 43
    bool approveLoan(const CreditScore& score, double amount) const; // Уникальное поведение 44
};

// 5. Вспомогательные классы (5 классов)
class CustomerService {
private:
    std::string department;
    int availableAgents;
public:
    CustomerService(const std::string& dept, int agents);
    bool handleComplaint(const std::string& complaint); // Уникальное поведение 45
    int estimateWaitTime(int queueLength) const;    // Уникальное поведение 46
};

class SecuritySystem {
private:
    int securityLevel;
    std::vector<std::string> accessLogs;
public:
    SecuritySystem(int level);
    bool authenticateUser(const std::string& credentials); // Уникальное поведение 47
    void logSecurityEvent(const std::string& event); // Уникальное поведение 48
};

class AuditTrail {
private:
    std::vector<std::string> auditRecords;
public:
    AuditTrail();
    void recordTransaction(const Transaction& transaction); // Уникальное поведение 49
    bool verifyCompliance() const;                  // Уникальное поведение 50
};

class NotificationService {
private:
    std::vector<std::string> notificationChannels;
public:
    NotificationService();
    bool sendAlert(const std::string& message, const std::string& channel); // Уникальное поведение 51
    void scheduleReminder(const std::string& reminder, std::time_t time); // Уникальное поведение 52
};

class ReportGenerator {
private:
    std::string reportFormat;
public:
    ReportGenerator(const std::string& format);
    std::string generateFinancialReport(const Bank& bank) const; // Уникальное поведение 53
    std::string generateRiskReport(const RiskAssessor& assessor) const; // Уникальное поведение 54
};

} // namespace banking
} // namespace minimarket
