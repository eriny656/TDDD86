// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

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
    void show();
    /* Draw the tour on scene */
    void draw(QGraphicsScene* scene);
    /* Returns the number of points on tour*/
    int size();
    /* Returns the total distance of the tour*/
    double distance();
    /* Insert p using the nearest neighbour heuristic*/
    void insertNearest(Point p);
    /* Insert p using the smallest increase heuristic*/
    void insertSmallest(Point p);

private:
    Node *mainNode;

};

#endif // TOUR_H
