// This header file contains the interface
// for the Tour object.
//
// Created by
// Eric Nylander (eriny656)
// Samuel Blomqvist (sambl126)

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:

    /* The constructor for the tour object*/
    Tour();
    /* Testing */
    Tour(Point a, Point b, Point c, Point d);
    /* The destructor for the tour object*/
    ~Tour();
    /* Print the tour to standard output*/
    void show() const;
    /* Draw the tour on scene */
    void draw(QGraphicsScene* scene) const;
    /* Returns the number of points on tour*/
    int size() const;
    /* Returns the total distance of the tour*/
    double distance() const;
    /* Insert p using the nearest neighbour heuristic*/
    void insertNearest(Point p);
    /* Insert p using the smallest increase heuristic*/
    void insertSmallest(Point p);

private:
    // This is our first node in the Tour object.
    Node *mainNode;

};

#endif // TOUR_H
