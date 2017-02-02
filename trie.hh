#include <iostream>
#include <map>
#include <string>

class Trie
{
  public:
    class Element
    {
      public:
        bool isWord;
        std::map<char, Element*> chars;
      public:
        Element()
            : isWord(false)
        {}
    };

  public:
    Trie();
    void addWord(const std::string &word);
    bool hasWord(const std::string &word) const;
    std::pair<Trie::Element*, bool> partialWord(Element *cur, char c) const;
    void printAll() const;
    void printRec(std::string word_so_far, Element *cur) const;

  protected:
    Element *root;
};    
  

class Dictionary : public Trie
{
  public:
    Dictionary()
        :Trie()
    {}

    size_t loadWords(const std::string &path);
};

