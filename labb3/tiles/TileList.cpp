// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"

TileList::TileList()
{
    tileArray = new Tile[size];
}

TileList::~TileList()
{
    delete [] tileArray;
}

void TileList::addTile(Tile tile)
{
    cout << size << endl;
    for (int var = 0; var < size-1; ++var) { // Double check -1
        tileArray[var] = tileArray[var+1];
    }
    tileArray[size-1] = tile;
}

void TileList::drawAll(QGraphicsScene* scene)
{
    for (int var = 0; var < size; ++var) { // Double check -1
        tileArray[var].draw(scene);
    }
}

int TileList::indexOfTopTile(int x, int y)
{
    for (int var = size-1; var >= 0; --var) {
        if(tileArray[var].contains(x, y)) {
            cout << tileArray[var].toString() << endl;
            cout << var << endl;
            return var;
        }
    }
    return -1;
}

void TileList::raise(int x, int y)
{
    int index = indexOfTopTile(x, y);
    if(index != -1) {
        Tile tempTile = tileArray[index];
        for (index; index < size-1; ++index) {
            tileArray[index] = tileArray[index+1];
        }
        cout << index << endl;
        tileArray[index] = tempTile;
    }
}

void TileList::lower(int x, int y)
{
    int index = indexOfTopTile(x, y);
    if(index != -1) {
        Tile tempTile = tileArray[index];
        for (index; index > 0; --index) {
            tileArray[index] = tileArray[index-1];
        }
        cout << index << endl;
        tileArray[index] = tempTile;
    }
}

void TileList::remove(int x, int y)
{
    int index = indexOfTopTile(x, y);
    if(index != -1){
        for (index; index > 0; --index){
            tileArray[index] = tileArray[index-1];
        }
        Tile tile;
        tileArray[index] = tile;
        cout << index << endl;
    }
    /*
    if(index != -1) {
        for (index; index < tileArray.size()-1; ++index) {
            tileArray[index] = tileArray[index+1];
        }
        Tile tile;
        tileArray[index] = tile;
        cout << index << endl;
    }
    */
}

void TileList::removeAll(int x, int y)
{
    while(indexOfTopTile(x, y) >= 0){
        remove(x, y);
    }
}
