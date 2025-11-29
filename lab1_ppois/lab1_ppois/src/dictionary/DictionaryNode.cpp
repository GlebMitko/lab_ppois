#include "../../include/dictionary/DictionaryNode.hpp"

namespace dictionary {

DictionaryNode::DictionaryNode(const std::string& eng, const std::string& rus)
    : englishWord(eng)
    , russianTranslation(rus)
    , left(nullptr)
    , right(nullptr) {
}

}
