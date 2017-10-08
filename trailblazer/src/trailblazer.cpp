// sambl126
// eriny656

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
        rVector.push_back(start);
        start->setColor(GREEN);

        for (Arc* arc: start->arcs) {
            if(!arc->finish->visited) {
                arc->finish->setColor(YELLOW);
                arc->finish->visited = true;
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
    start->visited = true;
    return dfs(graph, start, end);
}

vector<Node *> reconstructPath(Node* end) {
    vector<Node*> path;
    while(end->previous != nullptr) {
        end->setColor(GREEN);
        path.push_back(end);
        end = end->previous;
    }
    end->setColor(GREEN);
    path.push_back(end);

    reverse(path.begin(), path.end());
    return path;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    queue<Node *> bfsQueue;
    Vertex *current;

    graph.resetData();
    start->visited = true;
    bfsQueue.push(start);
    while(!bfsQueue.empty()) {
        current = bfsQueue.front();
        bfsQueue.pop();
        current->setColor(YELLOW);

        if(current->name == end->name) {
            return reconstructPath(current);
        } else {
            for(Arc *arc: current->arcs) {
                if(!arc->finish->visited) {
                    arc->finish->visited = true;
                    arc->finish->previous = current;
                    bfsQueue.push(arc->finish);
                }
            }
        }
    }
    graph.resetData();

    vector<Node *> emptyPath;
    return emptyPath;
}

void visitNode(Node *newNode, Node *previous, PriorityQueue<Vertex *> &pQueue, double priority, double cost) {
    newNode->visited = true;
    newNode->previous = previous;
    newNode->cost = cost;
    newNode->setColor(YELLOW);
    pQueue.enqueue(newNode, priority);
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    PriorityQueue<Vertex*> pQueue;
    graph.resetData();

    visitNode(start, nullptr, pQueue, 0, 0);

    double distToNeighbor = 0;
    Node *current;

    while(!pQueue.isEmpty()) {
        current = pQueue.dequeue();

        if(current->name == end->name) {
            return reconstructPath(current);
        }

        for(Arc *arc: current->arcs){
            distToNeighbor = current->cost + arc->cost;
            if(!arc->finish->visited) {
                visitNode(arc->finish, current, pQueue, distToNeighbor, distToNeighbor);

            } else if(distToNeighbor < arc->finish->cost) {
                pQueue.changePriority(arc->finish, distToNeighbor);
                arc->finish->cost = distToNeighbor;
                arc->finish->previous = current;
            }
        }
    }

    vector<Node *> emptyPath;
    return emptyPath;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    PriorityQueue<Vertex*> pQueue;
    graph.resetData();

    double heuristicEstimate = start->heuristic(end);
    visitNode(start, nullptr, pQueue, heuristicEstimate, 0);

    double distToNeighbor = 0;
    Node *current;

    while(!pQueue.isEmpty()) {
        current = pQueue.dequeue();

        if(current->name == end->name) {
            return reconstructPath(current);
        }

        for(Arc *arc: current->arcs){
            distToNeighbor = current->cost + arc->cost;
            heuristicEstimate = distToNeighbor + arc->finish->heuristic(end);

            if(!arc->finish->visited) {
                visitNode(arc->finish, current, pQueue, heuristicEstimate, distToNeighbor);

            } else if(distToNeighbor < arc->finish->cost) {
                pQueue.changePriority(arc->finish, heuristicEstimate);
                arc->finish->cost = distToNeighbor;
                arc->finish->previous = current;
            }
        }
    }

    vector<Node *> emptyPath;
    return emptyPath;
}
