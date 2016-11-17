// TDDD86 TileList
// This file contains the declaration for the TileList structure
// See TileList.cpp for implementation of each member
//
// Creates an editable list of tiles that are drawn and manipulated
// by the client
//
// Created by
// Eric Nylander (eriny656)
// Samuel Blomqvist (sambl126)

#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"
#include <array>

class TileList {
public:
    /*
     * Create new list of tiles
    */
    TileList();
    /*
     * Destructor of dynamically allocated memory
    */
    ~TileList();
    /*
     * Places tile at top of list
     */
    void addTile(Tile tile);
    /*
     * Draws all tiles in the list in the order of their appearance.
     */
    void drawAll(QGraphicsScene* scene);
    /*
     * Returns the index of the top tile at the given x, y coordinate.
     * If there is no tile, returns -1
     */
    int indexOfTopTile(int x, int y);
    /*
     * If the position is covered by a tile, the tile is shifted to the bottom of the list
     */
    void lower(int x, int y);
    /*
     * If the position is covered by a tile, the tile is shifted to the top of the list
     */
    void raise(int x, int y);
    /*
     * Removes the top tile at the given x, y coordinate
     * Reorganizes the remaining elements
     */
    void remove(int x, int y);
    /*
     * Removes all tiles at the given x, y coordinate.
     * Reorganizes the remaining elements.
     */
    void removeAll(int x, int y);

private:
    // Contains the array of tiles to be edited by the client
    Tile *tileArray;
    // Contains the size of the array
    int size;

};

#endif // TILELIST_H
