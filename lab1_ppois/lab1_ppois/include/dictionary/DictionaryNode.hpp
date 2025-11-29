#pragma once

#include <string>
#include <memory>

namespace dictionary {

class DictionaryNode {
public:
    std::string englishWord;
    std::string russianTranslation;
    std::unique_ptr<DictionaryNode> left;
    std::unique_ptr<DictionaryNode> right;
    
    DictionaryNode(const std::string& eng, const std::string& rus);
    ~DictionaryNode() = default;
    
    DictionaryNode(const DictionaryNode&) = delete;
    DictionaryNode& operator=(const DictionaryNode&) = delete;
};

}
