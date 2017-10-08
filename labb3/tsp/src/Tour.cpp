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


Tour::Tour() {
    mainNode = new Node(Point(0,0));
}

Tour::Tour(Point a, Point b, Point c, Point d)
{
    Node* nodeA = new Node(a);
    Node* nodeB = new Node(b, nodeA);
    nodeA->next = nodeB;
    Node* nodeC = new Node(c, nodeA);
    nodeB->next = nodeC;
    Node* nodeD = new Node(d, nodeA);
    nodeC->next = nodeD;
    mainNode = nodeA;
}

Tour::~Tour()
{
    Node* tempNode = mainNode->next;
    Node* nextNode;
    while(tempNode != mainNode){
        nextNode = tempNode->next;
        delete tempNode;
        tempNode = nextNode;
    }
    delete mainNode;
}

void Tour::show() const
{
    Node *tmpNode = mainNode->next;
    cout << mainNode->toString() << endl;

    if(tmpNode != nullptr){
        while(tmpNode != mainNode){
            cout << tmpNode->toString() << endl;
            tmpNode = tmpNode->next;
        }
    }
}

/*
 * Draws the tour to a scene.
 *
 *  * param:   QGraphicsScene *scene:
 *                  a pointer to the scene we
 *                  can draw our nodes onto.
 */
void Tour::draw(QGraphicsScene *scene) const
{
    Node *tmpNode = mainNode->next;

    if(tmpNode != nullptr){
        do{
            tmpNode->point.drawTo(tmpNode->next->point, scene);
            tmpNode = tmpNode->next;
        }
        while(tmpNode != mainNode->next);
    }
}

/*
 * Calculates the amount of Nodes in the tour.
 *
 *  * return: integer   an integer stating the amount
 *                      of nodes in the tour.
 */
int Tour::size() const
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
double Tour::distance() const
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
        delete mainNode;
        mainNode = new Node(p, nullptr);
        mainNode->next = mainNode;
    } else {
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
    }
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
        delete mainNode;
        mainNode = new Node(p, nullptr);
        mainNode->next = mainNode;
    } else {
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
    }
}
