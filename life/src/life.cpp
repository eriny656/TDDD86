// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <string>
#include <iostream>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"

using namespace std;

string convertToOutput(Grid<char> &grid);
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
        getline(myfile, line);
        rows = stoi(line);
        getline(myfile, line);
        columns = stoi(line);

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


int checkCellsInMinorSquare(int x, int y, Grid<char> grid) {
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
    int GRID_Y = grid.numRows();
    int GRID_X = grid.numCols();
    int cellsAmt;
    char tempChar;

    Grid<char> tempGrid = Grid<char>(GRID_Y, GRID_X);

    for (int y = 0; y < GRID_Y; ++y) {
        for (int x = 0; x < GRID_X; ++x) {
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
    int running = 1;

    while (running) {
        clearConsole();
        tick(grid);
        cout << convertToOutput(grid) << endl;
        pause(100);
    }
}


string convertToOutput(Grid<char>& grid){
    string gridString = "";
    for (int y = 0; y < grid.numRows(); ++y) {
        for (int x = 0; x < grid.numCols(); ++x) {
            gridString.push_back(grid[y][x]);
        }
        gridString.append("\n");
    }
    return gridString;
}
