// sambl126
// eriny656

#include "encoding.h"
#include <stdio.h>
#include <math.h>
#include <queue>
#include <iterator>

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    char character;

    while(input.get(character) ){
        int asciiChar = character;
        if(freqTable.find(asciiChar) != freqTable.end()) {
            ++freqTable[asciiChar];
        }
        else {
            freqTable.insert(pair<int, int>(asciiChar, 1));
        }
    }
    freqTable.insert(pair<int, int>(PSEUDO_EOF, 1));

    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
   priority_queue<HuffmanNode> huffQueue;
    for(pair<int, int> pr : freqTable) {
        huffQueue.push(HuffmanNode(pr.first, pr.second, nullptr, nullptr));
    }

    while(huffQueue.size() > 1) {
        HuffmanNode* node1 = new HuffmanNode(huffQueue.top());
        huffQueue.pop();
        HuffmanNode* node2 = new HuffmanNode(huffQueue.top());
        huffQueue.pop();
        huffQueue.push(HuffmanNode(NOT_A_CHAR, (node1->count + node2->count), node1, node2));
    }

    return new HuffmanNode(huffQueue.top().character, huffQueue.top().count, huffQueue.top().zero, huffQueue.top().one);
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    if(encodingTree == nullptr)
    {
        return encodingMap;
    }
    else if(encodingTree->isLeaf())
    {
        encodingMap[encodingTree->character] = "";
        return encodingMap;
    }

    map<int, string> leftMap = buildEncodingMap(encodingTree->zero);
    for(pair<const int, string> &pr: leftMap)
    {
        pr.second = "0" + pr.second;
    }

    map<int, string> rightMap = buildEncodingMap(encodingTree->one);
    for(pair<const int, string> &pr: rightMap)
    {
        pr.second = "1" + pr.second;
    }

    encodingMap.insert(leftMap.begin(), leftMap.end());
    encodingMap.insert(rightMap.begin(), rightMap.end());

    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    char c;
    string encoding;

    while(input.get(c))
    {
        encoding = encodingMap.at(c);

        for(char letter: encoding)
        {
            output.writeBit(letter-'0');
        }
    }
    encoding = encodingMap.at(PSEUDO_EOF);
    for(char letter: encoding)
    {
        output.writeBit(letter-'0');
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* currentNode = encodingTree;
    char c;

    while(true)
    {
        c = input.readBit() + '0';
        if(c == '1')
            currentNode = currentNode->one;
        else if (c == '0')
            currentNode = currentNode->zero;

        if(currentNode->isLeaf())
        {
            if(currentNode->character == PSEUDO_EOF)
                break;

            char nodeChar = currentNode->character;
            output << nodeChar;
            currentNode = encodingTree;
        }
    }
}

void compress(istream& input, obitstream& output) {
    map<int, int> frequencyTable = buildFrequencyTable(input);
    HuffmanNode* tree = buildEncodingTree(frequencyTable);
    map<int, string> encodingMap = buildEncodingMap(tree);

    stringstream ss;
    for(pair <int, int> pr : frequencyTable) {
        ss << to_string(pr.first);
        ss << ':';
        ss << pr.second;
        ss << ',';
    }
    string out;
    ss >> out;
    out.erase(out.length()-1, out.length()); // Remove trailing comma
    output << '{' << out << '}';

    input.clear();
    input.seekg(0,ios::beg);

    encodeData(input, encodingMap, output);
    freeTree(tree);
}

map<int, int> mappify(string const& s)
{
    map<int, int> m;

    using idx = decltype(s.size());

    idx key_pos = 0;
    idx key_end;
    idx val_pos;
    idx val_end;

    while((key_end = s.find(':', key_pos)) != string::npos)
    {
        if((val_pos = s.find_first_not_of(":", key_end)) == string::npos)
            break;

        val_end = s.find(',', val_pos);
        m.emplace(stoi(s.substr(key_pos, key_end - key_pos)), stoi(s.substr(val_pos, val_end - val_pos)));

        key_pos = val_end;
        if(key_pos != string::npos)
            ++key_pos;
    }

    return m;
}

void decompress(ibitstream& input, ostream& output) {
    map<int, int> freqTable;
    HuffmanNode* encodingTree;
    char c;
    string mapString;

    // Eliminate first { character before loop
    input >> c;
    input >> c;

    while(c != '}') {
        mapString += c;
        input >> c;
    }

    freqTable = mappify(mapString);
    encodingTree = buildEncodingTree(freqTable);

    decodeData(input, encodingTree, output);
    freeTree(encodingTree);
}

void freeTree(HuffmanNode* node) {
    if(node != nullptr) {
        if(!node->isLeaf()){
            freeTree(node->zero);
            freeTree(node->one);
        }
        delete node;
    }
}
