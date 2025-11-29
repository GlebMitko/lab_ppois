#include <iostream>

void runDictionaryTests();
void runBigIntTests();
void runStringUtilsTests();

int main() {
    std::cout << "Starting Unit Tests...\n\n";
    
    runDictionaryTests();
    runBigIntTests();
    runStringUtilsTests();
    
    std::cout << "🎉 ALL TESTS COMPLETED SUCCESSFULLY! 🎉\n";
    return 0;
}
