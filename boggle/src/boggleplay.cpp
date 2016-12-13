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
    clearConsole();
    printBoard(boggle);

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

    for(unsigned i=0; i<pow(boggle->BOARD_SIZE, 2); ++i){
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
