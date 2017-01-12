// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>
#include "bogglemain.h"
#include "strlib.h"
#include <utility>
// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle* boggle) {
    vector<string> userWords;
    string newWord;
    int score = 0;
    clearConsole();

    while (true) {
		// Printing the info on user's turn.
		cout << "It's your turn!" << endl;
		printBoard(boggle);
        if(userWords.size() > 0){
            cout << "Your words (" << userWords.size() << "): " << showWords(userWords) << endl;
        }
		cout << endl << "Your score: " << score << endl;

		cout << "Type a word (or press ENTER to end your turn): ";
		getline(cin, newWord);
		if (newWord == "") break;

        newWord = trim(toLowerCase(newWord));
        cout << endl;

        // If the word is not valid length, loop again
        if(isWordShort(newWord, boggle->MIN_WORD_LENGTH)) continue;

        // if the word already has been found, loop again
        if(isWordInList(newWord, userWords)) continue;

        if(!isWordInBoard(trim(toUpperCase(newWord)), boggle->getBoard())){
            clearConsole();
            cout << "That word is not in the board" << endl << endl;
            continue;
        }

        // if the word is not in the dictionary, loop again
        if (lexicon.contains(newWord)) {
            // clearConsole();
            userWords.push_back(trim(toUpperCase(newWord)));
			score += 1;
            cout << "You found a new word: " << newWord << endl;
			continue;
		}
		else {
			cout << "That was not a valid english word! Try again!" << endl;
		}
	}
		
	// Now it is the computer player's turn.
	// Implement that here.
    cout << endl << "It's my turn!" << endl;
    vector<string> botWords = botPlay(boggle);
    cout << "My words (" << botWords.size() << "): ";
    cout << showWords(botWords) << endl;
    cout << "My score: " << botWords.size() << endl;
    if(botWords.size() > score){
        cout << "BOTWIN" << endl;
    }
    else{
        cout << "HUMNWIN!" << endl;
    }

}

bool isWordInBoard(string newWord, const Grid<string> grid){
    int row = 0;
    int col = 0;
    vector<pair<int, int>> searchedPositions;
    while(grid.inBounds(row,col)){
        while(grid.inBounds(row,col)){
            char compChar = *grid.get(row,col).c_str();
            cout << compChar << " " << newWord << endl;
            if(newWord.at(0) == compChar){
                cout << "FIRST LETTER" << endl;
                if(findCompleteWord(newWord, grid, row, col, searchedPositions)){
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

bool findCompleteWord(string word, const Grid<string> grid, int row, int col, vector<pair<int, int>> &searchedPositions){
    searchedPositions.push_back(make_pair(row, col));
    word.erase(word.begin());
    cout << word << endl;
    if(word.length() == 0){
        return true;
    }
    for(int currentRow = row-1; currentRow < row+2; ++currentRow){
        if(!grid.inBounds(currentRow, 0)) continue;
        for(int currentCol = col-1; currentCol < col+2; ++currentCol){
            if(!grid.inBounds(0, currentCol)) continue;
            if(alreadySearched(currentRow, currentCol, searchedPositions)) {
                cout << grid.get(currentRow, currentCol) << " " << "alreadySearched!" << endl;
                continue;
            }
            if(word.at(0) == *grid.get(currentRow, currentCol).c_str() && findCompleteWord(word, grid, currentRow, currentCol, searchedPositions)) {
                cout << "YEE B0I!!" << endl;
                return true;
            }
        }
    }
    searchedPositions.pop_back();
    return false;
}

bool alreadySearched(int &y , int &x, vector<pair<int, int>> &sp){
    for(pair<int, int> position: sp){
        if(y == position.first && x == position.second) {
            return true;
        }
    }
    return false;
}

vector<string> botPlay(Boggle *boggle) {
    Grid<string> grid = boggle->getBoard();
    vector<string> foundWords;
    Lexicon botLexicon("EnglishWords.dat");

    int row = 0;
    int col = 0;
    vector<pair<int, int>> searchedPositions;
    while(grid.inBounds(row,col)){
        while(grid.inBounds(row,col)){
            string prefix = grid.get(row,col).c_str();
            botFindCompleteWord(prefix, boggle, row, col, searchedPositions, foundWords, botLexicon);
            ++col;
        }
        col = 0;
        ++row;
    }
    return foundWords;
}

void botFindCompleteWord(string prefix, Boggle *boggle, int row, int col, vector<pair<int, int>> &searchedPositions, vector<string> &foundWords, Lexicon botLexicon){
    //word.erase(word.begin());
    //cout << word << endl;
    //if(word.length() == 0){
    //    return true;
    //}
    if(!botLexicon.containsPrefix(prefix)) {
        return;
    }
    searchedPositions.push_back(make_pair(row, col));

    for(int currentRow = row-1; currentRow < row+2; ++currentRow){
        if(!boggle->getBoard().inBounds(currentRow, 0)) continue;
        for(int currentCol = col-1; currentCol < col+2; ++currentCol){
            if(!boggle->getBoard().inBounds(0, currentCol)) continue;
            if(alreadySearched(currentRow, currentCol, searchedPositions)) {
                cout << boggle->getBoard().get(currentRow, currentCol) << " " << "alreadySearched!" << endl;
                continue;
            }
            string tempPrefix = prefix;
            tempPrefix.append(boggle->getBoard().get(currentRow, currentCol));

            if(!isWordShort(tempPrefix, boggle->MIN_WORD_LENGTH) && botLexicon.contains(tempPrefix)){
                if(!isWordInList(tempPrefix, foundWords)) {
                    foundWords.push_back(tempPrefix);
                }
            }
            botFindCompleteWord(tempPrefix, boggle, currentRow, currentCol, searchedPositions, foundWords, botLexicon);
        }
    }
    searchedPositions.pop_back();
    return;
}







/*
 * Determines whether or not the entered word is in the english dictionary
*/
bool isDictionaryWord(string word) {
    // TODO: implement the binary search function to do this
    for (string dicWord: lexicon){
        if(word == dicWord) return true;
    }

    return false;
}


/*
 * Returns true if newWord is shorter than minLength
 */
bool isWordShort(string &newWord, const unsigned minLength){
    if (newWord.length() < minLength){
        clearConsole();
        cout << "Words that you enter must be at least " << minLength << " characters long." << endl;
        cout << "Please try again!" << endl;
        return true;
    }
    return false;
}

/*
 * Returns true if newWord exists in userWords
 */
bool isWordInList(string &newWord, vector<string> &userWords){
    string uppercaseWord = trim(toUpperCase(newWord));
    for (string word : userWords) {
        cout << endl << word << " + " << newWord << endl;
        if (word == uppercaseWord) {
            clearConsole();
            cout << "You've already entered that word before!" << endl;
            cout << "Please enter a new word or end your turn!" << endl << endl;
            return true;
        }
    }
    return false;
}

/*
 * Creates a string representation of the words that the user already
 * has entered.
 */
string showWords(vector<string>& words) {
	string wordString = "{";
    wordString.append(words.at(0));
    for (unsigned i = 1; i < words.size(); ++i) {
        wordString.append(", ");
        wordString.append(words.at(i));
	}
	wordString.append("}");

	return wordString;
}

/*
 * Prints the board that the player is using
 */
void printBoard(Boggle* boggle){
    Grid<string> board = boggle->getBoard();
    string printedBoard;
    int ypos;
    int xpos;

    for(unsigned i=0; i<boggle->getBoardArea(); ++i){
        if(i%boggle->BOARD_SIZE == 0){
            printedBoard.append("\n");
        }
        ypos = floor(i/boggle->BOARD_SIZE);
        xpos = i - (ypos * boggle->BOARD_SIZE);
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
