// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"
#include <array>

class TileList {
public:
    /*
     * Create new list with capacity 10
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
    Tile *tileArray;
    const int size = 10;

};

#endif // TILELIST_H
