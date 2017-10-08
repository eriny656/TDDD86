// sambl126
// eriny656

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <set>
#include "grid.h"
#include "lexicon.h"

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    Boggle();

    Boggle(string);

    ~Boggle();

    void buildBoard(string);

    void shuffleBoard();

    Grid<string> getBoard() const;

    unsigned getBoardArea() const;

    Boggle &operator=(const Boggle&);

    // Custom functions
    bool isWordInBoard(string newWord) const;
    bool findCompleteWord(string word, const int row, const int col, set<pair<int, int>> &searchedPositions) const;
    void botFindCompleteWord(string prefix, const int row, const int col, set<pair<int, int>> &searchedPositions, Lexicon botLexicon);
    bool isWordInList(string &newWord) const;
    bool isWordShort(const string &newWord) const;
    set<string> findBotWords(const Lexicon lex);
    set<string> getUserWords() const;
    void insertUserWord(const string word);

private:
    // Custom variables
    Grid<string> board;
    set<string> userWords;
    set<string> botWords;

};

#endif
