// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <queue>
#include <pqueue.h>
#include <stack>
#include <algorithm>
#include <limits>
using namespace std;


vector<Node *> dfs(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex *> rVector;
    vector<Vertex *> tmp;
    if(start->name == end->name) {
        rVector.push_back(start);
        start->setColor(GREEN);
    } else {
        start->visited = true;
        rVector.push_back(start);
        start->setColor(GREEN);

        for (Arc* arc: start->arcs) {
            if(!arc->finish->visited) {
                arc->finish->setColor(YELLOW);
                tmp = dfs(graph, arc->finish, end);
                if(!tmp.empty()) {
                    rVector.insert(rVector.end(), tmp.begin(), tmp.end());
                    return rVector;
                } else {
                    arc->finish->setColor(GRAY);
                    tmp.clear();
                }
            }
        }
        if(tmp.empty()) {
            rVector.clear();
        }
    }
    return rVector;
}

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    return dfs(graph, start, end);
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    queue<Node *> bfsQueue;
    Vertex *current;
    vector<Node *> rVector;

    graph.resetData();
    bfsQueue.push(start);
    while(!bfsQueue.empty()) {
        current = bfsQueue.front();
        bfsQueue.pop();
        current->visited = true;
        current->setColor(YELLOW);

        if(current->name == end->name) {
            do {
                rVector.push_back(current);
                current->setColor(GREEN);
                current = current->previous;
            } while(current != nullptr);
            reverse(rVector.begin(), rVector.end());
            graph.resetData();
            return rVector;
        } else {
            for(Arc *arc: current->arcs) {
                if(!arc->finish->visited) {
                    arc->finish->previous = current;
                    bfsQueue.push(arc->finish);
                }
            }
        }
    }
    graph.resetData();
    return rVector;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    PriorityQueue<Vertex*> pQueue;
    vector<Node *> path;

    graph.resetData();
    pQueue.enqueue(start, 0);
    start->cost = 0;
    start->visited = true;
    start->setColor(YELLOW);
    double distToNeighbor = 0;
    Node *current;

    while(!pQueue.isEmpty()) {
        current = pQueue.dequeue();

        if(current->name == end->name) {
            while(current->previous != nullptr) {
                current->setColor(GREEN);
                path.push_back(current);
                current = current->previous;
            }
            current->setColor(GREEN);
            path.push_back(current);

            reverse(path.begin(), path.end());
            return path;
        }

        for(Arc *arc: current->arcs){
            distToNeighbor = current->cost + arc->cost;
            if(!arc->finish->visited) {
                arc->finish->visited = true;
                arc->finish->previous = current;
                pQueue.enqueue(arc->finish, std::numeric_limits<double>::infinity());
                arc->finish->cost = std::numeric_limits<double>::infinity();
                arc->finish->setColor(YELLOW);
            }
            if(distToNeighbor < arc->finish->cost) {
                pQueue.changePriority(arc->finish, distToNeighbor);
                arc->finish->cost = distToNeighbor;
                arc->finish->previous = current;
            }
        }
    }

    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    PriorityQueue<Vertex*> pQueue;
    vector<Node *> path;

    graph.resetData();
    double heuristicEstimate = start->heuristic(end);
    pQueue.enqueue(start, heuristicEstimate);
    start->cost = 0;
    start->visited = true;
    start->setColor(YELLOW);
    double distToNeighbor = 0;
    Node *current;

    while(!pQueue.isEmpty()) {
        current = pQueue.dequeue();

        if(current->name == end->name) {
            while(current->previous != nullptr) {
                current->setColor(GREEN);
                path.push_back(current);
                current = current->previous;
            }
            current->setColor(GREEN);
            path.push_back(current);

            reverse(path.begin(), path.end());
            return path;
        }

        for(Arc *arc: current->arcs){
            distToNeighbor = current->cost + arc->cost;
            if(!arc->finish->visited) {
                arc->finish->visited = true;
                arc->finish->previous = current;
                pQueue.enqueue(arc->finish, std::numeric_limits<double>::infinity());
                arc->finish->cost = std::numeric_limits<double>::infinity();
                arc->finish->setColor(YELLOW);
            }
            if(distToNeighbor < arc->finish->cost) {
                heuristicEstimate = arc->finish->heuristic(end);
                pQueue.changePriority(arc->finish, distToNeighbor + heuristicEstimate);
                arc->finish->cost = distToNeighbor;
                arc->finish->previous = current;
            }
        }
    }

    return path;
}
