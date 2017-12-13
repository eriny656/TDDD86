// sambl126
// eriny656

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>
#include <set>
#include "bogglemain.h"
#include "strlib.h"
#include <utility>

const Lexicon lexicon("EnglishWords.dat");
const int INT_MAX = 2147483647;
string generateUserBoardString(unsigned area);
void printBoard(Boggle boggle);
string showWords(set<string> &words);
int score(const set<string> words);
bool checkLength(string &boardString, unsigned area);

/*
 * Plays one game of Boggle using the given a blank boggle game state object.
 */
void playOneGame(Boggle boggle) {
    string newWord;
    set<string> userWords;
    clearConsole();

    int area = boggle.getBoardArea();

    bool randBoard = yesOrNo("Do you want to generate a random board? ");
    if(!randBoard){
        boggle.buildBoard(generateUserBoardString(area));
    }

    while (true) {
        userWords.clear();

		// Printing the info on user's turn.
		cout << "It's your turn!" << endl;
		printBoard(boggle);

        userWords = boggle.getUserWords();
        if(!userWords.empty()){
            cout << "Your words (" << userWords.size() << "): " << showWords(userWords) << endl;
        }
        cout << endl << "Your score: " << score(userWords) << endl;

		cout << "Type a word (or press ENTER to end your turn): ";
		getline(cin, newWord);
		if (newWord == "") break;

        newWord = trim(toLowerCase(newWord));
        cout << endl;

        // If the word is not valid length, loop again
        if(boggle.isWordShort(newWord)) {
            clearConsole();
            cout << "Words that you enter must be at least " << boggle.MIN_WORD_LENGTH << " characters long." << endl;
            cout << "Please try again!" << endl;
            continue;
        }

        // if the word already has been found, loop again
        if(userWords.find(newWord) != userWords.end()) {
            clearConsole();
            cout << "You've already entered that word before!" << endl;
            cout << "Please enter a new word or end your turn!" << endl << endl;
            continue;
        }

        if(!boggle.isWordInBoard(trim(toUpperCase(newWord)))){
            clearConsole();
            cout << "That word is not in the board" << endl << endl;
            continue;
        }

        // if the word is not in the dictionary, loop again
        if (lexicon.contains(newWord)) {
            boggle.insertUserWord(trim(toUpperCase(newWord)));
            cout << "You found a new word: " << newWord << endl;
		}
		else {
			cout << "That was not a valid english word! Try again!" << endl;
		}
	}

    cout << endl << "It's my turn!" << endl;
    set<string> botWords = boggle.findBotWords(lexicon);
    cout << "My words (" << botWords.size() << "): ";
    cout << showWords(botWords) << endl;
    cout << "My score: " << score(botWords) << endl;
    if(score(botWords) > score(userWords)){
        cout << "BOTWIN" << endl;
    }
    else{
        cout << "HUMNWIN!" << endl;
    }

}

int score(const set<string> words) {
    int points = 0;
    for(string word: words) {
        points += word.length() - 3;
    }
    return points;
}

/*
 * Permits the user to create a custom board to play on
 */
string generateUserBoardString(unsigned area){
    string boardString;
    cout << endl <<  "Please enter the string of " << area << " characters you wish to use as your board" << endl;

    while (!checkLength(boardString, area)){}

    return boardString;
}

bool checkLength(string &boardString, unsigned area) {
    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    cin >> boardString;

    // clear the input buffer
    cin.ignore(INT_MAX, '\n');
    boardString = trim(toUpperCase(boardString));
    if(boardString.length() != area){
        cout << "Please enter a string of length " << area << " characters!" << endl;
        return false;
    }

    for(char character: boardString){
        int charPos = ALPHABET.find(character, 0);
        if(charPos == string::npos){
            cout << "Please enter a string of characters in the english alphabet!" << endl;
            return false;
        }
    }

    return true;
}

/*
 * Determines whether or not the entered word is in the english dictionary
*/
bool isDictionaryWord(string word) {
    for (string dicWord: lexicon){
        if(word == dicWord) return true;
    }
    return false;
}

/*
 * Creates a string representation of the words that the user already
 * has entered.
 */
string showWords(set<string>& words) {
	string wordString = "{";
    for(string word : words) {
        wordString.append(word);
        wordString.append(", ");
    }
    if(!words.empty())
        wordString.erase(wordString.end()-2, wordString.end());
    wordString.append("}");
    return wordString;
}

/*
 * Prints the board that the player is using
 */
void printBoard(Boggle boggle){
    Grid<string> board = boggle.getBoard();
    string printedBoard;
    int ypos;
    int xpos;

    for(unsigned i = 0; i < boggle.getBoardArea(); ++i){
        if(i % boggle.BOARD_SIZE == 0){
            printedBoard.append("\n");
        }
        ypos = floor(i / boggle.BOARD_SIZE);
        xpos = i - (ypos * boggle.BOARD_SIZE);
        printedBoard.append(board.get(ypos, xpos));
    }

    cout << printedBoard << endl;
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
