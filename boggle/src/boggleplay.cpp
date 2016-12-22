// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle* boggle) {
    vector<string> userWords;
    string newWord;
    int score = 0;
	bool skip;
	clearConsole();

	while (true) {
		skip = false;
		// Printing the info on user's turn.
		cout << "It's your turn!" << endl;
		printBoard(boggle);
		cout << "Your words (" << userWords.size() << "): " << showUserWords(userWords) << endl;
		cout << endl << "Your score: " << score << endl;

		cout << "Type a word (or press ENTER to end your turn): ";
		getline(cin, newWord);
		if (newWord == "") break;
		else if (newWord.length() < boggle->MIN_WORD_LENGTH) {
			clearConsole();
			cout << "Words that you enter must be at least " << boggle->MIN_WORD_LENGTH << " characters long." << endl;
			cout << "Please try again!" << endl;
			continue;
		}

		newWord = trim(toUpperCase(newWord));
		cout << endl;

		for (string word : userWords) {
			cout << endl << word << " + " << newWord << endl;
			if (word == newWord) {
				clearConsole();
				cout << "You've already entered that word before!" << endl;
				cout << "Please enter a new word or end your turn!" << endl;
				skip = true;
				break;
			}
		}
		if (skip) continue;

		if (isValidWord(newWord)) {
			clearConsole();
			userWords.push_back(newWord);
			score += 1;
			cout << "You found a new word!" << endl;
			continue;
		}
		else {
			cout << "That was not a valid english word! Try again!" << endl;
		}
	}
		
	// Now it is the computer player's turn.
	// Implement that here.

}

    // TODO: implement this function (and add any other functions you like to help you)


/*
 * Determines whether or not the entered word is in the english dictionary
*/
bool isValidWord(string& word) {
	// DEBUG
	// TODO: implement the binary search function to do this
	return true;
}

/*
 * Creates a string representation of the words that the user already
 * has entered.
 */
string showUserWords(vector<string>& userWords) {
	string wordString = "{";
	for (string word : userWords) {
		wordString.append(word);
		wordString.append(" ");
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
