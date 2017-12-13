// sambl126, eriny656

#include <sstream>
#include <math.h>
#include <iostream>
#include <set>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

using namespace std;

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle(){
    board.resize(BOARD_SIZE, BOARD_SIZE);
    string boardString;
    string cubeString;
    int charPosition;

    // Builds the string of random characters to be inserted in the grid
    for(int i = 0; i < NUM_CUBES; ++i){
        cubeString = CUBES[i];
        charPosition = randomInteger(0, CUBE_SIDES-1);
        cubeString = cubeString.at(charPosition);
        boardString.append(cubeString);
    }

    buildBoard(boardString);
    shuffle(board);
}

Boggle::~Boggle(){}

Boggle &Boggle::operator=(const Boggle &boggle){
    this->board = boggle.board;
    return *this;
}

Grid<string> Boggle::getBoard() const{
    return board;
}

unsigned Boggle::getBoardArea() const{
    return (BOARD_SIZE * BOARD_SIZE);
}

void Boggle::buildBoard(string boardString){
    int xpos;
    int ypos;
    string letter;

    for(int i = 0; i < NUM_CUBES; ++i){
        letter = boardString.at(i);
        ypos = floor(i/BOARD_SIZE);
        xpos = i - (BOARD_SIZE*ypos);

        board.set(ypos, xpos, letter);
    }
}

bool Boggle::isWordInBoard(string newWord) const{
    int row = 0;
    int col = 0;
    set<pair<int, int>> searchedPositions;
    while(board.inBounds(row,col)){
        while(board.inBounds(row,col)){
            char compChar = *board.get(row,col).c_str();
            if(newWord.at(0) == compChar){
                if(findCompleteWord(newWord, row, col, searchedPositions)){
                    return true;
                }
            }
            ++col;
        }
        col = 0;
        ++row;
    }
    return false;
}

bool Boggle::findCompleteWord(string word, const int row, const int col, set<pair<int, int>> &searchedPositions) const {
    searchedPositions.insert(make_pair(row, col));
    word.erase(word.begin());
    if(word.length() == 0){
        return true;
    }
    for(int currentRow = row - 1; currentRow < row + 2; ++currentRow){
        if(!board.inBounds(currentRow, 0)) continue;
        for(int currentCol = col - 1; currentCol < col + 2; ++currentCol){
            if(!board.inBounds(0, currentCol)) continue;
            if(searchedPositions.find(make_pair(currentRow, currentCol)) != searchedPositions.end()) {
                continue;
            }
            if(word.at(0) == *board.get(currentRow, currentCol).c_str() && findCompleteWord(word, currentRow, currentCol, searchedPositions)) {
                return true;
            }
        }
    }
    searchedPositions.erase(make_pair(row, col));
    return false;
}

void Boggle::botFindCompleteWord(string prefix, const int row, const int col, set<pair<int, int>> &searchedPositions, Lexicon botLexicon){
    if(botLexicon.containsPrefix(prefix)) {
        searchedPositions.insert(make_pair(row, col));

        for(int currentRow = row - 1; currentRow < row + 2; ++currentRow){
            if(!board.inBounds(currentRow, 0)) continue;
            for(int currentCol = col - 1; currentCol < col + 2; ++currentCol){
                if(!board.inBounds(0, currentCol)) continue;
                if(searchedPositions.find(make_pair(currentRow, currentCol)) != searchedPositions.end()) {
                    continue;
                }
                string tempPrefix = prefix;
                tempPrefix.append(board.get(currentRow, currentCol));

                if(!isWordShort(tempPrefix) && botLexicon.contains(tempPrefix)){
                    botWords.insert(tempPrefix);
                }
                botFindCompleteWord(tempPrefix, currentRow, currentCol, searchedPositions, botLexicon);
            }
        }

        searchedPositions.erase(make_pair(row, col));
    }
}

/*
 * Returns true if newWord exists in userWords
 */
bool Boggle::isWordInList(const string &newWord) const{
    string uppercaseWord = trim(toUpperCase(newWord));
    for (string word : userWords) {
        if (word == uppercaseWord) {
            return true;
        }
    }
    return false;
}

/*
 * Returns true if newWord is shorter than minLength
 */
bool Boggle::isWordShort(const string &newWord) const{
    return newWord.length() < MIN_WORD_LENGTH;
}

set<string> Boggle::findBotWords(const Lexicon lex){
    int row = 0;
    int col = 0;
    set<pair<int, int>> searchedPositions;
    while(board.inBounds(row,col)){
        while(board.inBounds(row,col)){
            string prefix = board.get(row,col).c_str();
            botFindCompleteWord(prefix, row, col, searchedPositions, lex);
            ++col;
        }
        col = 0;
        ++row;
    }
    return botWords;
}

set<string> Boggle::getUserWords() const{
    return userWords;
}

void Boggle::insertUserWord(const string word) {
    userWords.insert(word);
}



