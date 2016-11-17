// This file contains the implementation of
// the TileList object.
//
// Created by
// Eric Nylander (eriny656)
// Samuel Blomqvist (sambl126)

#include "TileList.h"


/*
 * The TileList constructor.
 */
TileList::TileList()
{
    size = 0;
    tileArray = new Tile[size];
}


/*
 *The TileList destructor.
 */
TileList::~TileList()
{
    delete [] tileArray;
}


/*
 * Takes a tile and recreates a new copy of tileArray
 * with the new tile inserted.
 *
 *  * param:   Tile tile:
 *                  The tile which will be added
 *                  to the new tileArray.
 */
void TileList::addTile(Tile tile)
{
    Tile *tmpArray = new Tile[++size];
    cout << size << endl;
    for (int var = 0; var < size-1; ++var) {
        tmpArray[var] = tileArray[var];
    }
    tmpArray[size-1] = tile;
    tileArray = tmpArray;
}


/*
 * Draws all the tiles in our tileArray.
 *
 *  * param:   QGraphicsScene *scene:
 *                  a pointer to the scene we
 *                  can draw the tiles to.
 */
void TileList::drawAll(QGraphicsScene* scene)
{
    for (int var = 0; var < size; ++var) { // Double check -1
        tileArray[var].draw(scene);
    }
}


/*
 * Gives an int value referring to the index of the
 * top tile at the given coordinates. Returns -1
 * if no tile was found.
 *
 *  * param:   int x:
 *                  the x-coordinate for which pixel
 *                  on the scene we are
 *                  investigating
 *
 *  * param:   int y:
 *                  the x-coordinate for which pixel
 *                  on the scene we are
 *                  investigating
 *
 *  * return: integer   the index value of the top tile
 *                      at the given coordinates.
 *                      Returns -1 if no tile was found.
 */
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

/*
 * Puts the top tile found at the given coordinates
 * in index 0 of the tileArray, putting it in the top.
 *
 *
 *  * param:   int x:
 *                  the x-coordinate for which pixel
 *                  on the scene we are
 *                  investigating
 *
 *  * param:   int y:
 *                  the x-coordinate for which pixel
 *                  on the scene we are
 *                  investigating
 *
 */
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
    int tileIndex = indexOfTopTile(x, y);
    if(tileIndex != -1){
        Tile *tmpArray = new Tile[--size];
        for (int index = tileIndex-1; index >= 0; --index){
            tmpArray[index] = tileArray[index];
        }
        for (int index = tileIndex; index < size; ++index){
            tmpArray[index] = tileArray[index+1];
        }
        tileArray = tmpArray;
    }
}

void TileList::removeAll(int x, int y)
{
    while(indexOfTopTile(x, y) >= 0){
        remove(x, y);
    }
}
