#pragma once
#include <stdexcept>
#include <string>

namespace minimarket {
namespace exceptions {

// 1. Недостаточно средств
class InsufficientFundsException : public std::runtime_error {
public:
    explicit InsufficientFundsException(const std::string& accountNumber)
        : std::runtime_error("Insufficient funds in account: " + accountNumber) {}
};

// 2. Недействительная карта
class InvalidCardException : public std::runtime_error {
public:
    explicit InvalidCardException(const std::string& cardNumber)
        : std::runtime_error("Invalid card: " + cardNumber) {}
};

// 3. Нарушение безопасности
class SecurityViolationException : public std::runtime_error {
public:
    explicit SecurityViolationException(const std::string& operation)
        : std::runtime_error("Security violation in operation: " + operation) {}
};

// 4. Товар не найден
class ProductNotFoundException : public std::runtime_error {
public:
    explicit ProductNotFoundException(const std::string& productId)
        : std::runtime_error("Product not found: " + productId) {}
};

// 5. Неверный пароль
class InvalidPasswordException : public std::runtime_error {
public:
    explicit InvalidPasswordException(const std::string& requirement)
        : std::runtime_error("Invalid password: " + requirement) {}
};

// 6. Ошибка обработки заказа
class OrderProcessingException : public std::runtime_error {
public:
    explicit OrderProcessingException(const std::string& orderId)
        : std::runtime_error("Order processing failed for: " + orderId) {}
};

// 7. Ошибка платежа
class PaymentFailedException : public std::runtime_error {
public:
    explicit PaymentFailedException(const std::string& paymentId)
        : std::runtime_error("Payment failed: " + paymentId) {}
};

// 8. Недостаток запасов
class InventoryShortageException : public std::runtime_error {
public:
    explicit InventoryShortageException(const std::string& productId)
        : std::runtime_error("Inventory shortage for product: " + productId) {}
};

// 9. Пользователь не аутентифицирован
class UserNotAuthenticatedException : public std::runtime_error {
public:
    explicit UserNotAuthenticatedException(const std::string& userId)
        : std::runtime_error("User not authenticated: " + userId) {}
};

// 10. Неверная операция
class InvalidOperationException : public std::runtime_error {
public:
    explicit InvalidOperationException(const std::string& operation)
        : std::runtime_error("Invalid operation: " + operation) {}
};

// 11. Ошибка валидации данных
class DataValidationException : public std::runtime_error {
public:
    explicit DataValidationException(const std::string& field)
        : std::runtime_error("Data validation failed for field: " + field) {}
};

// 12. Ошибка конфигурации системы
class SystemConfigurationException : public std::runtime_error {
public:
    explicit SystemConfigurationException(const std::string& component)
        : std::runtime_error("System configuration error in: " + component) {}
};

} // namespace exceptions
} // namespace minimarket
