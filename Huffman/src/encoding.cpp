// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include <stdio.h>
#include <math.h>
#include <queue>
#include <iterator>
// TODO: include any other headers you need

bool inMap(int&, map<int, int>&);

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    char character;
    int asciiChar;

    while(input.get(character) ){
        asciiChar = (int) character;
        if(inMap(asciiChar, freqTable)) {
            ++freqTable[asciiChar];
        }
        else {
            freqTable.insert(pair<int, int>(asciiChar, 1));
        }
    }
    freqTable.insert(pair<int, int>(PSEUDO_EOF, 1));

    return freqTable;
}

bool inMap(int& i, map<int, int>& m){
    for(pair<int, int> tempPair : m) {
        if(tempPair.first == i) {
            return true;
        }
    }
    return false;
}


HuffmanNode* createSubTree(HuffmanNode* oldTop, queue<HuffmanNode> q) {
    if(q.empty()) {
        return nullptr;
    }
    HuffmanNode left = q.front();
    q.pop();
    HuffmanNode* leftPointer = &left;
    if(q.empty()) {
        return new HuffmanNode(NOT_A_CHAR, oldTop->count + left.count, leftPointer, oldTop);
    }
    HuffmanNode right = q.front();
    q.pop();
    HuffmanNode* rightPointer = &right;
    HuffmanNode* mid = new HuffmanNode(NOT_A_CHAR, left.count + right.count, leftPointer, rightPointer);
    HuffmanNode* newCoolNode = new HuffmanNode(NOT_A_CHAR, mid->count + oldTop->count, mid, oldTop);
    return createSubTree(newCoolNode, q);
}


HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    map<int, int> tempTable = freqTable;

    queue<HuffmanNode> huffQueue;
    pair<int, int> tmpPair = *(tempTable.begin());
    int lowestKey = tmpPair.first;
    tempTable.erase(tempTable.end());
    while(huffQueue.size() < tempTable.size()) {
        for(pair<int, int> p : tempTable) {
            if (p.first < lowestKey) {
                lowestKey = p.first;
            }
        }
        huffQueue.push(*(new HuffmanNode(lowestKey, (*(tempTable.find(lowestKey))).second, nullptr, nullptr)));
        tempTable.erase(tempTable.find(lowestKey));
    }
    return createSubTree(new HuffmanNode(PSEUDO_EOF, 1, nullptr, nullptr), huffQueue);
}


map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    map<int, string> encodingMap;
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
