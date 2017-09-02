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

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
   priority_queue<HuffmanNode> huffQueue;
    for(pair<int, int> pr : freqTable) {
        huffQueue.push(HuffmanNode(pr.first, pr.second, nullptr, nullptr));
    }

    while(huffQueue.size() > 1) {
        HuffmanNode* node1 = new HuffmanNode(huffQueue.top().character, huffQueue.top().count, huffQueue.top().zero, huffQueue.top().one);
        huffQueue.pop();
        HuffmanNode* node2 = new HuffmanNode(huffQueue.top().character, huffQueue.top().count, huffQueue.top().zero, huffQueue.top().one);
        huffQueue.pop();
        huffQueue.push(HuffmanNode(NOT_A_CHAR, (node1->count + node2->count), node1, node2));
    }

    return new HuffmanNode(huffQueue.top().character, huffQueue.top().count, huffQueue.top().zero, huffQueue.top().one);
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
