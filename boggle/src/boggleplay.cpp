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
    int score;

    while(true){
        clearConsole();
        cout << "It's your turn!" << endl;
        printBoard(boggle);
        showUserWords(userWords);
        cout << score << endl;

        while(true){
            cout << "Type a word (or press ENTER to end your turn): ";
            cin >> newWord;
            if(newWord.length() < boggle->MIN_WORD_LENGTH){
                cout << "Words that you enter must be at least " << boggle->MIN_WORD_LENGTH << " characters long." << endl;
                cout << "Please try again!" << endl;
                continue;
            }

            newWord = trim(toUpperCase(newWord));
            cout << endl;

            for(string word: userWords){
                if(word == newWord){
                    cout << "You've already entered that word before!" << endl;
                    cout << "Please enter a new word or end your turn!" << endl;
                    continue;
                }
            }

            if(isValidWord(newWord)){
                userWords.push_back(newWord);
                score += 1;
                cout << "You found a new word!" << endl;
                break;
            }
            else{
                cout << "That was not a valid english word! Try again!" << endl;
            }
        }

    }

    // TODO: implement this function (and add any other functions you like to help you)

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
