#include "../../include/dictionary/Dictionary.hpp"
#include "../../include/utils/StringUtils.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

namespace dictionary {

const size_t MAX_WORD_LENGTH = 100;
const std::string DELIMITER = ":";

Dictionary::Dictionary() : root(nullptr), wordCount(0) {
}

Dictionary::Dictionary(const Dictionary& other) : wordCount(other.wordCount) {
    copyTree(other.root, root);
}

Dictionary& Dictionary::operator=(const Dictionary& other) {
    if (this != &other) {
        root.reset();
        wordCount = other.wordCount;
        copyTree(other.root, root);
    }
    return *this;
}


bool Dictionary::addWordInternal(const std::string& english, const std::string& russian) {
    if (english.empty()) {
        return false;
    }
    
    std::string engLower = utils::StringUtils::toLower(utils::StringUtils::trim(english));
    std::string rusTrimmed = utils::StringUtils::trim(russian);
    

    
    if (engLower.length() > MAX_WORD_LENGTH || rusTrimmed.length() > MAX_WORD_LENGTH) {
        return false;
    }
    
    bool result = insertWord(root, engLower, rusTrimmed);
    if (result) {
        wordCount++;
    }
    return result;
}

bool Dictionary::addWord(const std::string& english, const std::string& russian) {
    
    if (english.empty() || russian.empty()) {
        return false;
    }
    
    std::string engLower = utils::StringUtils::toLower(utils::StringUtils::trim(english));
    std::string rusTrimmed = utils::StringUtils::trim(russian);
    
    
    if (engLower.length() > MAX_WORD_LENGTH || rusTrimmed.length() > MAX_WORD_LENGTH) {
        return false;
    }
    
    bool result = insertWord(root, engLower, rusTrimmed);
    
    if (result) {
        wordCount++;
    }
    
    return result;
}

bool Dictionary::addWord(const char* english, const char* russian) {
    return addWord(std::string(english), std::string(russian));
}

Dictionary& Dictionary::operator+=(const std::pair<std::string, std::string>& pair) {
    addWord(pair.first, pair.second);
    return *this;
}

Dictionary& Dictionary::operator+=(const std::pair<const char*, const char*>& pair) {
    addWord(pair.first, pair.second);
    return *this;
}

bool Dictionary::removeWord(const std::string& english) {
    if (english.empty()) {
        return false;
    }
    
    std::string engLower = utils::StringUtils::toLower(utils::StringUtils::trim(english));
    bool result = deleteWord(root, engLower);
    if (result) {
        wordCount--;
    }
    return result;
}

bool Dictionary::removeWord(const char* english) {
    return removeWord(std::string(english));
}

Dictionary Dictionary::operator-(const std::string& english) const {
    Dictionary result(*this);
    result -= english;
    return result;
}

Dictionary Dictionary::operator-(const char* english) const {
    return operator-(std::string(english));
}

Dictionary& Dictionary::operator-=(const std::string& english) {
    removeWord(english);
    return *this;
}

Dictionary& Dictionary::operator-=(const char* english) {
    return operator-=(std::string(english));
}


std::string Dictionary::operator[](const std::string& english) const {
    if (english.empty()) {
        return "";
    }
    
    std::string engLower = utils::StringUtils::toLower(utils::StringUtils::trim(english));
    

    const DictionaryNode* current = root.get();
    while (current != nullptr) {
        if (engLower < current->englishWord) {
            current = current->left.get();
        } else if (engLower > current->englishWord) {
            current = current->right.get();
        } else {
            return current->russianTranslation;
        }
    }
    
    return "";
}


std::string& Dictionary::operator[](const std::string& english) {
    if (english.empty()) {
        static std::string empty;
        return empty;
    }
    
    std::string engLower = utils::StringUtils::toLower(utils::StringUtils::trim(english));
    DictionaryNode* node = findWordForModification(root, engLower);
    
    if (!node) {
        bool added = addWordInternal(engLower, "");
        if (added) {
            node = findWordForModification(root, engLower);
        }
    }
    
    if (node) {
        return node->russianTranslation;
    } else {
        static std::string empty;
        return empty;
    }
}

size_t Dictionary::getWordCount() const {
    return wordCount;
}

bool Dictionary::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    root.reset();
    wordCount = 0;
    
    file >> *this;
    return true;
}

bool Dictionary::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << *this;
    return true;
}

bool Dictionary::operator==(const Dictionary& other) const {
    if (wordCount != other.wordCount) {
        return false;
    }
    return compareTrees(root.get(), other.root.get());
}

bool Dictionary::operator!=(const Dictionary& other) const {
    return !(*this == other);
}


DictionaryNode* Dictionary::findWord(DictionaryNode* node, const std::string& english) const {
    DictionaryNode* current = node;
    while (current != nullptr) {
        if (english < current->englishWord) {
            current = current->left.get();
        } else if (english > current->englishWord) {
            current = current->right.get();
        } else {
            return current;
        }
    }
    return nullptr;
}

DictionaryNode* Dictionary::findWordForModification(std::unique_ptr<DictionaryNode>& node, const std::string& english) {
        if (!node) {
            return nullptr;
        }
        
    if (!node) {
        return nullptr;
    }
    
    if (english < node->englishWord) {
        return findWordForModification(node->left, english);
    } else if (english > node->englishWord) {
        return findWordForModification(node->right, english);
    } else {
        return node.get();
    }
}

bool Dictionary::insertWord(std::unique_ptr<DictionaryNode>& node, const std::string& english, const std::string& russian) {
        if (!node) {
            node = std::make_unique<DictionaryNode>(english, russian);
            return true;
        }
        
    if (!node) {
        node = std::make_unique<DictionaryNode>(english, russian);
        return true;
    }
    
    if (english < node->englishWord) {
        return insertWord(node->left, english, russian);
    } else if (english > node->englishWord) {
        return insertWord(node->right, english, russian);
    } else {
        node->russianTranslation = russian;
        return false;
    }
}

bool Dictionary::deleteWord(std::unique_ptr<DictionaryNode>& node, const std::string& english) {
    if (!node) {
        return false;
    }
    
    if (english < node->englishWord) {
        return deleteWord(node->left, english);
    } else if (english > node->englishWord) {
        return deleteWord(node->right, english);
    } else {
        if (!node->left && !node->right) {
            node.reset();
        } else if (!node->left) {
            node = std::move(node->right);
        } else if (!node->right) {
            node = std::move(node->left);
        } else {
            DictionaryNode* minNode = findMin(node->right.get());
            node->englishWord = minNode->englishWord;
            node->russianTranslation = minNode->russianTranslation;
            deleteWord(node->right, minNode->englishWord);
        }
        return true;
    }
}

DictionaryNode* Dictionary::findMin(DictionaryNode* node) const {
    while (node && node->left) {
        node = node->left.get();
    }
    return node;
}

void Dictionary::copyTree(const std::unique_ptr<DictionaryNode>& source, std::unique_ptr<DictionaryNode>& destination) {
    if (!source) return;
    
    destination = std::make_unique<DictionaryNode>(source->englishWord, source->russianTranslation);
    copyTree(source->left, destination->left);
    copyTree(source->right, destination->right);
}

bool Dictionary::compareTrees(const DictionaryNode* node1, const DictionaryNode* node2) const {
    if (!node1 && !node2) return true;
    if (!node1 || !node2) return false;
    
    return (node1->englishWord == node2->englishWord &&
            node1->russianTranslation == node2->russianTranslation &&
            compareTrees(node1->left.get(), node2->left.get()) &&
            compareTrees(node1->right.get(), node2->right.get()));
}

void Dictionary::printTree(std::ostream& os, const DictionaryNode* node) const {
    if (!node) return;
    
    printTree(os, node->left.get());
    os << node->englishWord << DELIMITER << " " << node->russianTranslation << "\n";
    printTree(os, node->right.get());
}

void Dictionary::readTree(std::istream& is, std::unique_ptr<DictionaryNode>& node) {
    std::string line;
    while (std::getline(is, line)) {
        if (line.empty()) continue;
        
        size_t delimiterPos = line.find(DELIMITER);
        if (delimiterPos == std::string::npos) continue;
        
        std::string english = utils::StringUtils::trim(line.substr(0, delimiterPos));
        std::string russian = utils::StringUtils::trim(line.substr(delimiterPos + 1));
        
        if (!english.empty() && !russian.empty()) {
            insertWord(node, english, russian);
            wordCount++;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Dictionary& dict) {
    dict.printTree(os, dict.root.get());
    return os;
}

std::istream& operator>>(std::istream& is, Dictionary& dict) {
    dict.readTree(is, dict.root);
    return is;
}

}
