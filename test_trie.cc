#include "trie.hh"

int main()
{
    Trie t;
    t.addWord("foo");
    t.addWord("bar");
    t.addWord("foobar");

    t.addWord("macbookpro");
    t.addWord("macbook");

    t.printAll();
    std::cout << "searching for macbook" << t.hasWord("macbook") << std::endl;
    std::cout << "searching for nonexistant" << t.hasWord("nonexistant") << std::endl;
    
    Trie::Element *cur = nullptr;
    for (auto c: "foobar") {
        auto s = t.partialWord(cur, c);
        if (s.first == nullptr)
            break;
        if (s.second)
            std::cout << "found word" << std::endl;
        cur = s.first;
    }
    if (!cur)
        std::cout << "didn't find word" << std::endl;

    Dictionary d;
    d.loadWords("dict.txt");
    d.printAll();
    return 0;
}

        

