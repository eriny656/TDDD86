// This file contains the implementation of
// the Tour object.
//
// Created by
// Eric Nylander (eriny656)
// Samuel Blomqvist (sambl126)

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"
#include <array>


/*
 * The Tour constructor
 */
Tour::Tour()
{
    mainNode = new Node(Point(0,0), nullptr);
}

/*
 * The Tour destructor
 */
Tour::~Tour()
{
    delete mainNode;
}

/*
 * Prints out the information of each Node in the tour.
 */
void Tour::show()
{
    Node *tmpNode = mainNode->next;
    cout << mainNode->toString() << endl;

    if(tmpNode == nullptr){
        return;
    }
    while(tmpNode != mainNode){
        cout << tmpNode->toString() << endl;
        tmpNode = tmpNode->next;
    }
}

/*
 * Draws the tour to a scene.
 *
 *  * param:   QGraphicsScene *scene:
 *                  a pointer to the scene we
 *                  can draw our nodes onto.
 */
void Tour::draw(QGraphicsScene *scene)
{
    Node *tmpNode = mainNode->next;

    if(tmpNode == nullptr){
        return;
    }
    do{
        tmpNode->point.drawTo(tmpNode->next->point, scene);
        tmpNode = tmpNode->next;
    }
    while(tmpNode != mainNode->next);
}

/*
 * Calculates the amount of Nodes in the tour.
 *
 *  * return: integer   an integer stating the amount
 *                      of nodes in the tour.
 */
int Tour::size()
{
    Node *tmpNode = mainNode->next;
    int size = 0;

    if(tmpNode == nullptr){
        return size;
    }
    do {
        ++size;
        tmpNode = tmpNode->next;
    }
    while(tmpNode != mainNode->next);
    return size;
}

/*
 * Calculates the total distance between
 * all Nodes in the tour.
 *
 *  * return: double    a double representing the
 *                      total distance.
 */
double Tour::distance()
{
    Node *tmpNode = mainNode->next;
    double distance = 0;

    if(tmpNode == nullptr || tmpNode == mainNode){
        return 0;
    }
    Node *previousNode = mainNode;
    do{
        distance += (previousNode->point.distanceTo(tmpNode->point));
        previousNode = tmpNode;
        tmpNode = tmpNode->next;
    }
    while(tmpNode != mainNode->next);
    return distance;
}

/*
 * Inserts a given point into the tour where
 * the shortest distance to another point has
 * been determined.
 *
 *  * param:   Point p:
 *                  The point which will be inserted.
 */
void Tour::insertNearest(Point p)
{
    Node *tmpNode = mainNode->next;

    if(tmpNode == nullptr){
        mainNode = new Node(p, nullptr);
        mainNode->next = mainNode;
        return;
    }

    double shortestDistance = mainNode->point.distanceTo(p);
    Node *nearestNode = mainNode;
    double distance;

    while(tmpNode != mainNode) {
        distance = tmpNode->point.distanceTo(p);
        if(distance < shortestDistance){
            nearestNode = tmpNode;
            shortestDistance = distance;
        }
        tmpNode = tmpNode->next;
    }
    Node *newNode = new Node(p, nearestNode->next);
    nearestNode->next = newNode;
    return;
}

/*
 * Inserts a given point into the tour where
 * the shortest TOTAL distance increase has been
 * determined.
 *
 *  * param:   Point p:
 *                  The point which will be inserted.
 */
void Tour::insertSmallest(Point p)
{
    Node *tmpNode = mainNode->next;

    if(tmpNode == nullptr){
        mainNode = new Node(p, nullptr);
        mainNode->next = mainNode;
        return;
    }

    double shortestDifference = -1;
    double difference;

    Node *nearestNode = mainNode;
    while(tmpNode != mainNode) {
        difference = (tmpNode->point.distanceTo(p) +
                      p.distanceTo(tmpNode->next->point)) -
                tmpNode->point.distanceTo(tmpNode->next->point);

        if(difference < shortestDifference || shortestDifference == -1){
            nearestNode = tmpNode;
            shortestDifference = difference;
        }
        tmpNode = tmpNode->next;
    }
    Node *newNode = new Node(p, nearestNode->next);
    nearestNode->next = newNode;
    return;
}
