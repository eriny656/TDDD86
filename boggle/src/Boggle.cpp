// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include <math.h>
#include <iostream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

using namespace std;

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static const int NUM_ROWS = 4;
static const int NUM_COLS = 4;
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle(){
    board.resize(NUM_ROWS, NUM_COLS);
    string boardString;
    string cubeString;
    int letterPosition;

    for(int i = 0; i < NUM_CUBES; ++i){
        cubeString = CUBES[i];
        letterPosition = randomInteger(0, CUBE_SIDES-1);
        cout << "finding letter position" << endl;
        cubeString = cubeString.at(letterPosition);
        boardString.append(cubeString);
    }
    cout << "building board" << endl;

    buildBoard(boardString);

    shuffle(board);

    cout << board.toString();
}

Boggle::Boggle(string userBoard){
    board.resize(NUM_ROWS, NUM_COLS);

    buildBoard(userBoard);
    shuffle(board);
}

Grid<string> Boggle::getBoard() const{
    return board;
}

void Boggle::buildBoard(string &boardString){
    int xpos;
    int ypos;
    string letter;

    for(int i = 0; i < NUM_CUBES; ++i){
        letter = boardString.at(i);
        ypos = floor(i/NUM_COLS);
        xpos = i - (NUM_COLS*ypos);

        board.set(ypos, xpos, letter);
    }
}
// TODO: implement the members you declared in Boggle.h
