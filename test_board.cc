#include <iostream>
#include "board.hh"

bool longest(std::string w1, std::string w2)
{
    return w1.size() > w2.size();
}


int main()
{
    Board b;
    Dictionary d;
    d.loadWords("dict.txt");
    b.loadBoard("board1.txt");
    b.printBoard();
    
    auto words = b.findLongestWords(d);
    std::sort(words.begin(), words.end(), longest);
    for (const auto &w: words) 
        std::cout << w << std::endl;
    return 0;
}

