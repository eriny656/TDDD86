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

Boggle::Boggle(string userBoard){
    board.resize(BOARD_SIZE, BOARD_SIZE);

    buildBoard(userBoard);
}

Boggle::~Boggle(){}

Boggle &Boggle::operator=(const Boggle &boggle){
    this->board = boggle.board;
    return *this;
}

Grid<string> Boggle::getBoard() const{
    return board;
}

int Boggle::getBoardArea(){
    return (BOARD_SIZE * BOARD_SIZE);
}

void Boggle::buildBoard(string &boardString){
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
// TODO: implement the members you declared in Boggle.h
