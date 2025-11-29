#pragma once

#include "DictionaryNode.hpp"
#include <string>
#include <memory>
#include <fstream>

namespace dictionary {

class Dictionary {
private:
    std::unique_ptr<DictionaryNode> root;
    size_t wordCount;
    bool addWordInternal(const std::string& english, const std::string& russian);

public:
    Dictionary();
    ~Dictionary() = default;
    Dictionary(const Dictionary& other);
    Dictionary& operator=(const Dictionary& other);
    

    bool addWord(const std::string& english, const std::string& russian);
    bool addWord(const char* english, const char* russian);
    Dictionary& operator+=(const std::pair<std::string, std::string>& pair);
    Dictionary& operator+=(const std::pair<const char*, const char*>& pair);
    

    bool removeWord(const std::string& english);
    bool removeWord(const char* english);
    Dictionary operator-(const std::string& english) const;
    Dictionary operator-(const char* english) const;
    Dictionary& operator-=(const std::string& english);
    Dictionary& operator-=(const char* english);
    

    std::string operator[](const std::string& english) const;
    std::string& operator[](const std::string& english);
    

    size_t getWordCount() const;
    

    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    

    bool operator==(const Dictionary& other) const;
    bool operator!=(const Dictionary& other) const;
    

    friend std::ostream& operator<<(std::ostream& os, const Dictionary& dict);
    friend std::istream& operator>>(std::istream& is, Dictionary& dict);

private:

    DictionaryNode* findWord(DictionaryNode* node, const std::string& english) const;
    DictionaryNode* findWordForModification(std::unique_ptr<DictionaryNode>& node, const std::string& english);
    

    bool insertWord(std::unique_ptr<DictionaryNode>& node, const std::string& english, const std::string& russian);
    bool deleteWord(std::unique_ptr<DictionaryNode>& node, const std::string& english);
    DictionaryNode* findMin(DictionaryNode* node) const;
    void copyTree(const std::unique_ptr<DictionaryNode>& source, std::unique_ptr<DictionaryNode>& destination);
    bool compareTrees(const DictionaryNode* node1, const DictionaryNode* node2) const;
    

    void printTree(std::ostream& os, const DictionaryNode* node) const;
    void readTree(std::istream& is, std::unique_ptr<DictionaryNode>& node);
};

}
