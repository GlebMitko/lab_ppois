#include "../include/dictionary/Dictionary.hpp"
#include <iostream>
#include <cassert>
#include <sstream>
#include <cstdio>

void testDictionaryConstructor() {
    dictionary::Dictionary dict;
    assert(dict.getWordCount() == 0);
    std::cout << "✅ testDictionaryConstructor: PASSED\n";
}

void testAddWord() {
    dictionary::Dictionary dict;
    assert(dict.addWord("hello", "привет"));
    assert(dict.getWordCount() == 1);
    std::cout << "✅ testAddWord: PASSED\n";
}

void testAddWordCharPtr() {
    dictionary::Dictionary dict;
    assert(dict.addWord("computer", "компьютер"));
    assert(dict.getWordCount() == 1);
    std::cout << "✅ testAddWordCharPtr: PASSED\n";
}

void testOperatorAdd() {
    dictionary::Dictionary dict;
    dict += std::make_pair("programming", "программирование");
    assert(dict.getWordCount() == 1);
    dict += std::make_pair("algorithm", "алгоритм");
    assert(dict.getWordCount() == 2);
    std::cout << "✅ testOperatorAdd: PASSED\n";
}

void testRemoveWord() {
    dictionary::Dictionary dict;
    dict.addWord("hello", "привет");
    dict.addWord("world", "мир");
    dict.addWord("computer", "компьютер");
    
    assert(dict.removeWord("hello"));
    assert(dict.getWordCount() == 2);
    assert(!dict.removeWord("nonexistent"));
    assert(dict.getWordCount() == 2);
    std::cout << "✅ testRemoveWord: PASSED\n";
}

void testComparison() {
    dictionary::Dictionary dict1;
    dict1.addWord("hello", "привет");
    dict1.addWord("world", "мир");
    
    dictionary::Dictionary dict2;
    dict2.addWord("hello", "привет");
    dict2.addWord("world", "мир");
    
    dictionary::Dictionary dict3;
    dict3.addWord("hello", "привет");
    
    assert(dict1 == dict2);
    assert(dict1 != dict3);
    std::cout << "✅ testComparison: PASSED\n";
}

void testCopyConstructor() {
    dictionary::Dictionary dict1;
    dict1.addWord("hello", "привет");
    dict1.addWord("world", "мир");
    
    dictionary::Dictionary dict2(dict1);
    assert(dict2.getWordCount() == 2);
    std::cout << "✅ testCopyConstructor: PASSED\n";
}

void testAssignmentOperator() {
    dictionary::Dictionary dict1;
    dict1.addWord("hello", "привет");
    dict1.addWord("world", "мир");
    
    dictionary::Dictionary dict2;
    dict2 = dict1;
    assert(dict2.getWordCount() == 2);
    std::cout << "✅ testAssignmentOperator: PASSED\n";
}

void testEdgeCases() {
    dictionary::Dictionary dict;
    

    assert(!dict.addWord("", "привет"));
    assert(!dict.addWord("hello", ""));
    

    std::string longWord(150, 'a');
    assert(!dict.addWord(longWord, "translation"));
    
    std::cout << "✅ testEdgeCases: PASSED\n";
}

void testLargeDictionary() {
    dictionary::Dictionary dict;
    

    for (int i = 0; i < 100; ++i) {
        dict.addWord("word" + std::to_string(i), "translation" + std::to_string(i));
    }
    
    assert(dict.getWordCount() == 100);
    
    std::cout << "✅ testLargeDictionary: PASSED\n";
}

void testOperatorAccess() {
    
    dictionary::Dictionary dict;
    

    dict.addWord("hello", "привет");
    

    std::string result = dict["hello"];
    assert(result == "привет");
    

    dict["world"] = "мир";
    
    
    std::cout << "✅ testOperatorAccess: PASSED\n";
}

void testOperatorAccessCharPtr() {
    
    dictionary::Dictionary dict;
    

    dict["computer"] = "компьютер";
    

    assert(dict.getWordCount() == 1);
    

    std::string translation = dict["computer"];
    assert(translation == "компьютер");
    

    dict["computer"] = "ЭВМ";
    assert(dict["computer"] == "ЭВМ");
    
    std::cout << "✅ testOperatorAccessCharPtr: PASSED\n";
}

void testFileOperations() {
    dictionary::Dictionary dict;
    dict.addWord("hello", "привет");
    dict.addWord("world", "мир");
    dict.addWord("computer", "компьютер");
    

    assert(dict.saveToFile("test_dict.txt"));
    

    dictionary::Dictionary loadedDict;
    assert(loadedDict.loadFromFile("test_dict.txt"));
    

    assert(loadedDict.getWordCount() == 3);
    assert(loadedDict["hello"] == "привет");
    assert(loadedDict["world"] == "мир");
    assert(loadedDict["computer"] == "компьютер");
    

    std::remove("test_dict.txt");
    
    std::cout << "✅ testFileOperations: PASSED\n";
}

void testStreamOperators() {
    dictionary::Dictionary dict;
    dict.addWord("apple", "яблоко");
    dict.addWord("banana", "банан");
    

    std::ostringstream oss;
    oss << dict;
    std::string output = oss.str();
    assert(!output.empty());
    assert(output.find("apple") != std::string::npos);
    assert(output.find("яблоко") != std::string::npos);
    

    std::istringstream iss("cherry: вишня\ndate: финик\n");
    dictionary::Dictionary newDict;
    iss >> newDict;
    
    assert(newDict.getWordCount() == 2);
    assert(newDict["cherry"] == "вишня");
    assert(newDict["date"] == "финик");
    
    std::cout << "✅ testStreamOperators: PASSED\n";
}

void testDictionaryCombinedOperations() {
    dictionary::Dictionary dict;
    

    dict += std::make_pair("one", "один");
    dict.addWord("two", "два");
    dict["three"] = "три";
    
    assert(dict.getWordCount() == 3);
    

    dict -= "two";
    assert(dict.getWordCount() == 2);
    
    dict["four"] = "четыре";
    assert(dict.getWordCount() == 3);
    

    dictionary::Dictionary dictCopy = dict;
    assert(dictCopy == dict);
    

    dictCopy["one"] = "единица";
    assert(dictCopy != dict);
    

    assert(dict["one"] == "один");
    assert(dict["three"] == "три");
    assert(dict["four"] == "четыре");
    assert(dictCopy["one"] == "единица");
    
    std::cout << "✅ testDictionaryCombinedOperations: PASSED\n";
}

void testDuplicateWords() {
    dictionary::Dictionary dict;
    

    assert(dict.addWord("test", "тест1"));
    assert(dict.getWordCount() == 1);
    

    assert(!dict.addWord("test", "тест2"));
    assert(dict.getWordCount() == 1);
    assert(dict["test"] == "тест2");
    
    std::cout << "✅ testDuplicateWords: PASSED\n";
}

void testBoundaryCases() {
    dictionary::Dictionary dict;
    

    std::string longWord(100, 'a');
    std::string longTranslation(100, 'b');
    assert(dict.addWord(longWord, longTranslation));
    

    std::string tooLongWord(150, 'a');
    assert(!dict.addWord(tooLongWord, "translation"));
    

    assert(!dict.removeWord("nonexistent"));
    
    std::cout << "✅ testBoundaryCases: PASSED\n";
}

void testCharPtrOperators() {
    dictionary::Dictionary dict;
    

    dict += std::make_pair("key", "value");
    dict -= "key";
    dict = dict - "nonexistent";
    

    assert(dict["hello"].empty());
    
    std::cout << "✅ testCharPtrOperators: PASSED\n";
}

void testMinusOperators() {
    dictionary::Dictionary dict;
    dict.addWord("hello", "привет");
    dict.addWord("world", "мир");
    

    dictionary::Dictionary dict2 = dict - "hello";
    assert(dict2.getWordCount() == 1);
    assert(dict2["world"] == "мир");
    

    dict2 -= "world";
    assert(dict2.getWordCount() == 0);
    
    std::cout << "✅ testMinusOperators: PASSED\n";
}

void testEmptyDictionary() {
    dictionary::Dictionary dict;
    

    assert(dict.getWordCount() == 0);
    assert(dict["nonexistent"].empty());
    assert(!dict.removeWord("word"));
    assert(dict == dict);
    
    dictionary::Dictionary dict2;
    
    std::cout << "✅ testEmptyDictionary: PASSED\n";
}

void testPlusEqualsOperators() {
    dictionary::Dictionary dict;
    

    dict += std::make_pair("key", "value");
    dict += std::make_pair("hello", "привет");
    
    assert(dict.getWordCount() == 2);
    assert(dict["key"] == "value");
    assert(dict["hello"] == "привет");
    
    std::cout << "✅ testPlusEqualsOperators: PASSED\n";
}

void testNotEqualOperator() {
    dictionary::Dictionary dict1;
    dict1.addWord("hello", "привет");
    
    dictionary::Dictionary dict2;
    dict2.addWord("hello", "здравствуйте");
    
    dictionary::Dictionary dict3;
    
    assert(dict1 != dict2);
    assert(dict1 != dict3);
    assert(dict2 != dict3);
    
    std::cout << "✅ testNotEqualOperator: PASSED\n";
}

void testRemoveNonExistent() {
    dictionary::Dictionary dict;
    dict.addWord("hello", "привет");
    

    assert(!dict.removeWord(""));
    assert(!dict.removeWord("nonexistent"));
    assert(!dict.removeWord("world"));
    

    assert(dict.getWordCount() == 1);
    assert(dict["hello"] == "привет");
    
    std::cout << "✅ testRemoveNonExistent: PASSED\n";
}

void testEmptyStringOperations() {
    dictionary::Dictionary dict;
    

    assert(!dict.addWord("", "translation"));
    assert(!dict.addWord("word", ""));
    assert(!dict.removeWord(""));
    assert(dict[""].empty());
    

    assert(dict.getWordCount() == 0);
    
    std::cout << "✅ testEmptyStringOperations: PASSED\n";
}

void testAllCharPtrVersions() {
    dictionary::Dictionary dict;
    

    assert(dict.addWord("test1", "translation1"));
    assert(dict.removeWord("test1"));
    
    dict += std::make_pair("test2", "translation2");
    dict -= "test2";
    
    dictionary::Dictionary dict3 = dict - "nonexistent";
    
    std::cout << "✅ testAllCharPtrVersions: PASSED\n";
}

void testCopyEmptyDictionary() {
    dictionary::Dictionary dict1;
    

    dictionary::Dictionary dict2(dict1);
    dictionary::Dictionary dict3;
    dict3 = dict1;
    
    assert(dict2.getWordCount() == 0);
    assert(dict3.getWordCount() == 0);
    
    std::cout << "✅ testCopyEmptyDictionary: PASSED\n";
}

void testEmptyDictionaryStreams() {
    dictionary::Dictionary dict;
    

    std::ostringstream oss;
    oss << dict;
    std::string output = oss.str();
    assert(output.empty());
    

    std::istringstream iss("");
    dictionary::Dictionary dict2;
    iss >> dict2;
    assert(dict2.getWordCount() == 0);
    
    std::cout << "✅ testEmptyDictionaryStreams: PASSED\n";
}

void testRemoveAllScenarios() {
    dictionary::Dictionary dict;
    

    dict.addWord("m", "root");
    dict.addWord("d", "left");
    dict.addWord("a", "left-left");
    dict.addWord("f", "left-right");
    dict.addWord("s", "right");
    dict.addWord("p", "right-left");
    dict.addWord("x", "right-right");
    assert(dict.removeWord("a"));
    assert(dict.getWordCount() == 6);
    assert(dict.removeWord("f"));
    assert(dict.getWordCount() == 5);
    assert(dict.removeWord("m"));
    assert(dict.getWordCount() == 4);
    std::cout << "✅ testRemoveAllScenarios: PASSED\n";
}

void testFileErrors() {
    dictionary::Dictionary dict;
    

    assert(!dict.loadFromFile("nonexistent_file.txt"));
    

    assert(!dict.saveToFile("/invalid/path/file.txt"));
    
    std::cout << "✅ testFileErrors: PASSED\n";
}

void testMixedOperators() {
    dictionary::Dictionary dict;
    

    dict += std::make_pair("one", "один");
    dict.addWord("two", "два");
    dict["three"] = "три";
    
    dictionary::Dictionary result = (dict - "two") - "three";
    result += std::make_pair("four", "четыре");
    
    assert(result.getWordCount() == 2);
    assert(result["one"] == "один");
    assert(result["four"] == "четыре");
    
    std::cout << "✅ testMixedOperators: PASSED\n";
}

void testAddWordInternalEmptyEnglish() {
    dictionary::Dictionary dict;
    
    dict[""] = "test";

    assert(dict.getWordCount() == 0);
    
    std::cout << "✅ testAddWordInternalEmptyEnglish: PASSED\n";
}

void testPlusEqualsOperator() {
    dictionary::Dictionary dict;
    

    dict += std::make_pair("hello", "привет");
    dict += std::make_pair("world", "мир");
    
    assert(dict.getWordCount() == 2);
    assert(dict["hello"] == "привет");
    assert(dict["world"] == "мир");
    
    std::cout << "✅ testPlusEqualsOperator: PASSED\n";
}

void testConstOperatorAccess() {
    dictionary::Dictionary dict;
    dict.addWord("hello", "привет");
    dict.addWord("world", "мир");
    

    const dictionary::Dictionary& constDict = dict;
    

    assert(constDict["hello"] == "привет");
    assert(constDict["world"] == "мир");
    assert(constDict["nonexistent"].empty());
    

    assert(constDict[""].empty());
    
    std::cout << "✅ testConstOperatorAccess: PASSED\n";
}

void testConstCharOperators() {
    dictionary::Dictionary dict;
    

    dict += std::make_pair("key", "value");
    dict = dict - "key";
    dict += std::make_pair("test", "test");
    dict -= "test";
    
    assert(dict.getWordCount() == 0);
    
    std::cout << "✅ testConstCharOperators: PASSED\n";
}

void testAddWordInternalEdgeCases() {
    dictionary::Dictionary dict;
    

    dict[""] = "test";
    assert(dict.getWordCount() == 0);
    
    std::cout << "✅ testAddWordInternalEdgeCases: PASSED\n";
}

void testPlusEqualsOperatorsComprehensive() {
    dictionary::Dictionary dict;
    

    dict += std::make_pair("hello", "привет");
    dict += std::make_pair("world", "мир");
    
    assert(dict.getWordCount() == 2);
    assert(dict["hello"] == "привет");
    assert(dict["world"] == "мир");
    
    std::cout << "✅ testPlusEqualsOperators: PASSED\n";
}

void testFindWordMethod() {
    dictionary::Dictionary dict;
    dict.addWord("hello", "привет");
    dict.addWord("world", "мир");
    
    assert(dict["hello"] == "привет");
    assert(dict["world"] == "мир");
    
    assert(dict["nonexistent"].empty());
    
    std::cout << "✅ testFindWordMethod: PASSED\n";
}

void testRemainingOperators() {
    dictionary::Dictionary dict;
    dict.addWord("test", "тест");
    
    dictionary::Dictionary result1 = dict - "test";
    assert(result1.getWordCount() == 0);
    assert(dict.getWordCount() == 1);
    
    dict -= "test";
    assert(dict.getWordCount() == 0);
    
    std::cout << "✅ testRemainingOperators: PASSED\n";
}

void testAllPlusEqualsVariants() {
    dictionary::Dictionary dict;
    
    dict += std::make_pair(std::string("hello"), std::string("привет"));
    
    dict += std::make_pair("world", "мир");
    
    assert(dict.getWordCount() == 2);
    assert(dict["hello"] == "привет");
    assert(dict["world"] == "мир");
    
    std::cout << "✅ testAllPlusEqualsVariants: PASSED\n";
}

void testExplicitConstCharOperators() {
    dictionary::Dictionary dict;
    
    dict.addWord("test1", "trans1");
    
    dict.removeWord("test1");
    
    dict += std::make_pair("test2", "trans2");
    
    dict -= "test2";
    
    dict.addWord("test3", "trans3");
    dictionary::Dictionary dict2 = dict - "test3";
    
    assert(dict2.getWordCount() == 0);
    
    std::cout << "✅ testExplicitConstCharOperators: PASSED\n";
}

void testFindWordIndirectly() {
    dictionary::Dictionary dict;
    
    dict.addWord("find", "найти");
    dict.addWord("test", "тест");
    
    assert(dict.removeWord("find"));
    
    const dictionary::Dictionary& constDict = dict;
    assert(constDict["test"] == "тест");
    assert(constDict["nonexistent"].empty());
    
    std::cout << "✅ testFindWordIndirectly: PASSED\n";
}


void runDictionaryTests() {
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "RUNNING DICTIONARY TESTS\n";
    std::cout << std::string(50, '=') << "\n";
    
    testDictionaryConstructor();
    testAddWord();
    testAddWordCharPtr();
    testOperatorAdd();
    testRemoveWord();
    testComparison();
    testCopyConstructor();
    testAssignmentOperator();
    testEdgeCases();
    testLargeDictionary();
    testOperatorAccess();
    testOperatorAccessCharPtr();
    testFileOperations();
    testStreamOperators();
    testDictionaryCombinedOperations();
    testDuplicateWords();
    testBoundaryCases();
    testCharPtrOperators();
    testMinusOperators();
    testEmptyDictionary();
    testPlusEqualsOperators();
    testNotEqualOperator();
    testRemoveNonExistent();
    testEmptyStringOperations();
    testAllCharPtrVersions();
    testCopyEmptyDictionary();
    testEmptyDictionaryStreams();
    testRemoveAllScenarios();
    testFileErrors();
    testMixedOperators();
    testAddWordInternalEmptyEnglish();
    testPlusEqualsOperator();
    testConstOperatorAccess();
    testConstCharOperators();
    testAddWordInternalEdgeCases();
    testPlusEqualsOperatorsComprehensive();
    testFindWordMethod();
    testRemainingOperators();
    testAllPlusEqualsVariants();
    testExplicitConstCharOperators();
    testFindWordIndirectly();
    
    std::cout << std::string(50, '=') << "\n";
    std::cout << "BASIC DICTIONARY TESTS PASSED! ✅\n";
    std::cout << std::string(50, '=') << "\n\n";
}
