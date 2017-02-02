#include <cassert>
#include <fstream>
#include <iostream>

#include "board.hh"

void
Board::loadBoard(const std::string &path)
{
    std::ifstream b;
    b.open(path);
    while (!b.eof()) {
        std::string line;
        std::getline(b, line);
        if (line.size() == 0)
            break;
        std::vector<char> bl(line.begin(), line.end());
        board.push_back(bl);
    }
}

void
Board::printBoard() const
{
    for (auto const &l: board) {
        for (auto const c: l)
            std::cout << c;
        std::cout << std::endl;
    }
}

char
Board::getchar(std::pair<size_t,size_t> loc)
{
    auto x = loc.first;
    auto y = loc.second;
    assert(x >= 0 && y >= 0 && x < board.size() && y < board[0].size());
    return board[x][y];
}

std::vector<std::pair<size_t,size_t>>
Board::moves(const std::vector<std::pair<size_t,size_t>> &cur_moves)
{
    std::vector<std::pair<size_t,size_t>> next_moves;

    for (int x : {-1, 0, 1}) {
        for (int y : {-1, 0, 1}) {
           auto next_move = *--cur_moves.end();
           next_move.first += x;
           next_move.second += y;
           if (next_move.first >= board.size() || (x == 0 && y == 0) || next_move.second >= board[0].size()) 
                // if we haven't moved or have fallen off the board skip this
                // one
                continue;
           auto it = std::find(cur_moves.begin(), cur_moves.end(), next_move);
           if (it != cur_moves.end())
               // make sure we don't repeat a position
               continue;
            next_moves.emplace_back(next_move);
        }
    }
    return next_moves;
}

std::vector<std::string>
Board::findLongestWords(const Dictionary &d)
{
    
    std::vector<std::string> words;
    for (size_t x = 0; x < board.size(); x++) {
        for (size_t y = 0; y < board[0].size(); y++) {
            auto p = d.partialWord(nullptr, board[x][y]);
            _findLongestWords(d, words,  {std::make_pair(x,y)}, p);
        }
    }
    return words;
}

void 
Board::_findLongestWords(const Dictionary &d, std::vector<std::string> &words, std::vector<std::pair<size_t,size_t>> cur_moves, 
        std::pair<Trie::Element*,bool> loc)
{
    if (loc.first == nullptr)
        // we've come to a dead-end in the Trie, try something else
        return;
    if (loc.second && cur_moves.size() > 2) {
        std::string word;
        for (auto const &pos: cur_moves) 
            word += board[pos.first][pos.second];
        words.emplace_back(word);
    }
    auto next_moves = moves(cur_moves);
    // add some junk to the list so the inner loop doesn't special case first iteration
    cur_moves.emplace_back(std::make_pair(-1,-1));
    for (auto m: next_moves)
    {
        cur_moves.pop_back();
        cur_moves.emplace_back(m);
        auto partial = d.partialWord(loc.first, board[m.first][m.second]);
        if (partial.first == nullptr)
            continue;
        _findLongestWords(d, words, cur_moves, partial);
    }
    cur_moves.pop_back();
}









