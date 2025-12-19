cmake_minimum_required(VERSION 3.10)
project(LabWork)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GCC coverage флаги (для Linux/gcov); для macOS можно оставить или убрать
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g --coverage")

# --- ИСТОЧНИКИ: USERS ---
set(USER_SOURCES
    src/users/User.cpp
    src/users/Customer.cpp
    src/users/Employee.cpp
    src/users/Admin.cpp
    src/users/UserProfile.cpp
    src/users/Address.cpp
    src/users/ContactInfo.cpp
    src/users/LoginCredentials.cpp
    src/users/UserSession.cpp
    src/users/UserPreferences.cpp
)

# --- ИСТОЧНИКИ: PRODUCTS ---
set(PRODUCT_SOURCES
    src/products/Product.cpp
    src/products/Category.cpp
    src/products/Inventory.cpp
    src/products/PricingStrategy.cpp
    src/products/DiscountSystem.cpp
    src/products/Supplier.cpp
    src/products/Warehouse.cpp
    src/products/BarcodeSystem.cpp
    src/products/ProductReview.cpp
    src/products/ProductSpecification.cpp
)

# --- ИСТОЧНИКИ: ORDERS ---
set(ORDER_SOURCES
    src/orders/Order.cpp
    src/orders/OrderItem.cpp
    src/orders/Payment.cpp
    src/orders/Shipping.cpp
    src/orders/ShoppingCart.cpp
)

# --- ИСТОЧНИКИ: BANKING ---
set(BANKING_SOURCES
    src/banking/Balance.cpp
    src/banking/Transaction.cpp
    src/banking/Account.cpp
    src/banking/Card.cpp
    src/banking/Bank.cpp
    src/banking/CreditCard.cpp
    src/banking/Loan.cpp
    src/banking/Mortgage.cpp
    src/banking/InvestmentAccount.cpp
    src/banking/CreditScore.cpp
    src/banking/ATM.cpp
    src/banking/Branch.cpp
    src/banking/BankTransfer.cpp
    src/banking/PaymentProcessor.cpp
    src/banking/BankStatement.cpp
    src/banking/FraudDetector.cpp
    src/banking/CurrencyConverter.cpp
    src/banking/InterestCalculator.cpp
    src/banking/TaxCalculator.cpp
    src/banking/RiskAssessor.cpp
    src/banking/CustomerService.cpp
    src/banking/SecuritySystem.cpp
    src/banking/AuditTrail.cpp
    src/banking/NotificationService.cpp
    src/banking/ReportGenerator.cpp
)

# --- ОСНОВНОЙ ИСПОЛНЯЕМЫЙ ФАЙЛ ---
add_executable(lab_work
    src/main.cpp
    ${USER_SOURCES}
    ${PRODUCT_SOURCES}
    ${ORDER_SOURCES}
    ${BANKING_SOURCES}
)
target_include_directories(lab_work PRIVATE include)

# --- ТЕСТЫ ---
add_executable(run_tests
    tests/main_test.cpp
    tests/test_banking.cpp
    tests/test_products.cpp
    tests/test_users.cpp
    tests/test_orders.cpp
    ${USER_SOURCES}
    ${PRODUCT_SOURCES}
    ${ORDER_SOURCES}
    ${BANKING_SOURCES}
)
target_include_directories(run_tests PRIVATE include)

# --- ТЕСТИРОВАНИЕ ---
enable_testing()
add_test(NAME AllTests COMMAND run_tests)

# --- COVERAGE (для Linux/gcov) ---
# На macOS gcov может не работать корректно; можно использовать llvm-cov при необходимости
add_custom_target(coverage
    COMMAND echo "=== CODE COVERAGE ANALYSIS ==="
    COMMAND ./run_tests
    COMMAND echo ""
    COMMAND echo "=== GENERATING COVERAGE REPORTS ==="
    COMMAND find . -name "*.gcno" -exec gcov -b -c -p {} \\; > /dev/null 2>&1 || true
    COMMAND echo ""
    COMMAND echo "✅ Coverage analysis completed (reports in .gcov files)"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS run_tests
)

# --- БЫСТРАЯ ПРОВЕРКА ---
add_custom_target(run-tests
    COMMAND echo "=== RUNNING TESTS ==="
    COMMAND ./run_tests
    COMMAND echo "✅ ALL TESTS PASSED"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS run_tests
)