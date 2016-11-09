// This file creates an instance of a text based
// representation of the Game of Life; a simulation
// of the lifecycle of a bacteria colony.
//
// Rules:
// 1. A cell with 1 or fewer neighbors dies
// 2. Locations with 2 neighbors remains stable
// 3. A cell with 4 or more neighbors dies
//
// Created by
// Eric Nylander (eriny656)
// Samuel Blomqvist (sambl126)

#include <string>
#include <iostream>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"

using namespace std;

string convertToOutput(const Grid<char> &grid);
void tick(Grid<char> &grid);
void animate(Grid<char> &grid);

int main() {
    string line;
    string filename;
    int running = 1;
    string keyInput;

    cout << "Welcome to the TDDD86 Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbours dies." << endl;
    cout << "- Locations with 2 neighbours remain stable." << endl;
    cout << "- A cell with 4 or more neighbours dies.\n" << endl;
    cout << "Grid input file name?" << endl;
    cin >> filename;

    ifstream myfile (filename);
    int rows;
    int columns;
    Grid<char> gameField;

    if (myfile.is_open()) {
        myfile >> rows >> columns;
        getline(myfile, line);

        gameField.resize(rows, columns);
        for (int y = 0; y < rows; ++y) {
            getline(myfile, line);
            for (int x = 0; x < columns; ++x) {
                char value = line[x];
                gameField.set(y, x, value);
            }
        }
        myfile.close();
    }

    cout << convertToOutput(gameField) << endl;



    cout << "a)nimate, t)ick, q)uit?" << endl;

    while (running) {
        cin >> keyInput;

        if (keyInput == "a") {
            cout << "Animate" << endl;
            animate(gameField);
            cout << "a)nimate, t)ick, q)uit?" << endl;
        }
        else if (keyInput == "t") {
            cout << "Tick" << endl;
            tick(gameField);
            cout << convertToOutput(gameField) << endl;
            cout << "a)nimate, t)ick, q)uit?" << endl;
        }
        else if (keyInput == "q") {
            cout << "Have a nice life!" << endl;
            running = 0;
        }
    }

    return 0;
}


int checkCellsInMinorSquare(int x, int y, const Grid<char>& grid) {
    int cellsAmt = 0;
    char tempChar;

    for (int row = y-1; row <= y+1; ++row) {
        for (int col = x-1; col <= x+1; ++col) {
            if (!grid.inBounds(row, col)) {
                continue;
            }
            tempChar = grid[row][col];
            if (tempChar == 'X') {
                ++cellsAmt;
            }
        }
    }
    return cellsAmt;
}


void tick(Grid<char>& grid) {
    int gridY = grid.numRows();
    int gridX = grid.numCols();
    int cellsAmt;
    char tempChar;

    Grid<char> tempGrid = Grid<char>(gridY, gridX);

    for (int y = 0; y < gridY; ++y) {
        for (int x = 0; x < gridX; ++x) {
            cellsAmt = checkCellsInMinorSquare(x, y, grid);
            tempChar = grid[y][x];
            if (tempChar == 'X') {
                --cellsAmt; // We do -1 since we don't count the current grid space as a neighbour.
            }

            if (cellsAmt <= 1 || cellsAmt >= 4) {
                tempGrid[y][x] = '-';
            }
            else if (cellsAmt == 2) {
                tempGrid[y][x] = grid[y][x];
            }
            else if (cellsAmt == 3) {
                tempGrid[y][x] = 'X';
            }
        }
    }
    grid = tempGrid;
}

void animate(Grid<char>& grid) {
    while (true) {
        clearConsole();
        tick(grid);
        cout << convertToOutput(grid) << endl;
        pause(500);
    }
}


string convertToOutput(const Grid<char>& grid){
    string gridString = "";
    for (int y = 0; y < grid.numRows(); ++y) {
        for (int x = 0; x < grid.numCols(); ++x) {
            gridString.push_back(grid[y][x]);
        }
        gridString.append("\n");
    }
    return gridString;
}
