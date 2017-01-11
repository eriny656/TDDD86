/*
 * TDDD86 Boggle
 * This file declares required function prototypes that are defined in
 * our provided bogglemain.cpp and your boggleplay.cpp that you will write.
 * See the respective .cpp files for implementation comments for each function.
 * Please do not modify this provided file.
 */

#ifndef _bogglemain_h
#define _bogglemain_h

#include "Boggle.h"
#include "lexicon.h"
#include <string>
using namespace std;

const Lexicon lexicon("EnglishWords.dat");

void intro();
void playOneGame(Boggle *boggle);
bool yesOrNo(string prompt);
void clearConsole();

Boggle* generateUserBoard(unsigned);
void printBoard(Boggle*);

string showUserWords(vector<string>&);
bool isDictionaryWord(string);
bool isWordShort(string&, const unsigned);
bool isWordInList(string&, vector<string>&);

bool isWordInBoard(string, const Grid<string>);
bool findCompleteWord(string, const Grid<string>, int, int, vector<pair<int, int>>&);
bool alreadySearched(int&, int&, vector<pair<int, int>>&);

#endif
