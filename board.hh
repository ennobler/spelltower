#include <string>
#include <vector>

#include "trie.hh"

class Board
{
  public:
    Board()
    {}

    void loadBoard(const std::string &path);

    std::vector<std::pair<size_t,size_t>> moves(const std::vector<std::pair<size_t,size_t>> &cur_moves);

    char getchar(std::pair<size_t,size_t> loc);

    void printBoard() const;

    std::vector<std::string> findLongestWords(const Dictionary &d);

  protected:
    void _findLongestWords(const Dictionary &d, std::vector<std::string>
            &words, std::vector<std::pair<size_t,size_t>> cur_moves,
            std::pair<Trie::Element*,bool> loc);
    std::vector<std::vector<char>> board;
} ;

