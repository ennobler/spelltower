#include <fstream>
#include <iostream>
#include <locale>
#include "trie.hh"

Trie::Trie()
{
    root = new Element();
}

void
Trie::addWord(const std::string &word)
{
    Element *cur = root;
    for (auto c: word) {
        auto s = cur->chars.find(c);
        if (s != cur->chars.end()) {
            cur = s->second;
        } else {
            cur->chars[c] = new Element;
            cur = cur->chars[c];
        }

    }
    cur->isWord = true;
}

bool
Trie::hasWord(const std::string &word) const
{
    Element *cur = root;
    for (auto c: word) {
        auto s = cur->chars.find(c);
        if (s == cur->chars.end())
            return false;
        cur = s->second;
    }
    if (cur->isWord)
        return true;
    return false;
}

std::pair<Trie::Element*, bool>
Trie::partialWord(Trie::Element *cur, char c) const
{
    if (cur == nullptr)
        cur = root;

    auto s = cur->chars.find(c);
    if (s == cur->chars.end())
        return std::make_pair(nullptr, false);
    cur = cur->chars[c];
    auto p = std::make_pair(cur, cur->isWord);
    return p;
}

void
Trie::printAll() const
{
    printRec("", root);
}

void
Trie::printRec(std::string word_so_far, Element *cur) const
{
    for (const auto &v: cur->chars) {
        if (v.second->isWord)
            std::cout << word_so_far + v.first << std::endl;
        printRec(word_so_far + v.first, v.second);
    }
}


size_t
Dictionary::loadWords(const std::string &path)
{
    size_t count = 0;
    std::ifstream dict;
    dict.open(path);
    while (!dict.eof()) {
        std::string line;
        std::getline(dict, line);
        if (line.size() == 0)
            break;
        std::string word = line.substr(line.rfind(' ') + 1);
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        addWord(word);
        count++;
    }
    std::cout << "Loaded " << count << " words into trie." << std::endl;
    return count;
}



