// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"
#include <array>

Tour::Tour()
{
    // TODO: write this member
}


Tour::Tour(Point a, Point b, Point c, Point d)
{
    Node *nodeA = new Node(a, nullptr);
    Node *nodeB = new Node(b, nullptr);
    Node *nodeC = new Node(c, nullptr);
    Node *nodeD = new Node(d, nodeA);
    nodeA->next = nodeB;
    nodeB->next = nodeC;
    nodeC->next = nodeD;

    mainNode = nodeA;
}

Tour::~Tour()
{
    // TODO: write this member
}

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

void Tour::insertNearest(Point p)
{
    Node *tmpNode = mainNode->next;

    if(tmpNode == nullptr){
        mainNode = new Node(p, mainNode);
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

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
