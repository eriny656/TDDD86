// This file takes two words as parameters and
// finds the shortest chain of words with a single
// edited letter between the two.
//
// Created by
// Eric Nylander (eriny656)
// Samuel Blomqvist (sambl126)

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
stack<string> wordChain(const string&, const string&);

int main() {
    string output;
    string startWord;
    string endWord;
    stack<string> chain;

    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";

    cin >> startWord >> endWord;

    chain = wordChain(startWord, endWord);

    while (!chain.empty()) {
        output.append(chain.top());
        chain.pop();
        output.append(", ");
    }
    cout << "Chain from " << endWord << " back to " <<  startWord << ":" << endl;
    cout << output << endl << "Have a nice day." << endl;

    return 0;
}

stack<string> wordChain(const string &w1, const string &w2) {
    queue<stack<string>> chainPaths;
    stack<string> path;
    string word;
    unordered_set<string> dictionary;
    ifstream dicStream;
    unordered_set<string> chainedWords;
    dicStream.open("dictionary.txt");

    while(dicStream >> word) {
        dictionary.insert(word);
    }

    // Create an empty queue of stacks
    // Create/add a stack containing {w1} to the queue

    path.push(w1);
    chainPaths.push(path);
    chainedWords.insert(w1);

    while (!chainPaths.empty()) {
        stack<string> tempStack = chainPaths.front();
        chainPaths.pop();
        string tempWord = tempStack.top();
        tempStack.pop();
        int checkedLetter = -1;

        if (tempWord == w2) {
            tempStack.push(tempWord);
            return tempStack;
        }

        // Determines the letter that was last edited in the stack
        // This letter does not need to be checked in the current
        // Iteration. This also solves the issue of looping paths
        if(!tempStack.empty()){
            string secondToLast = tempStack.top();
            for(unsigned int i = 0; i < tempWord.length(); ++i) {
                if(tempWord[i] != secondToLast[i]){
                    checkedLetter = i;
                    break;
                }
            }
        }

        for (unsigned int charIndex = 0; charIndex < tempWord.length(); ++charIndex) {
            if(charIndex == checkedLetter){
                continue;
            }

            for (char alphabetLetter:ALPHABET) {
                if (tempWord[charIndex] == alphabetLetter){
                    continue;
                }
                string changedWord = tempWord;
                changedWord[charIndex] = alphabetLetter;

                if (dictionary.find(changedWord) != dictionary.end()) {

                    if (chainedWords.find(changedWord) == chainedWords.end()) {

                        chainedWords.insert(changedWord);
                        stack<string> newStack = tempStack;
                        newStack.push(tempWord);
                        newStack.push(changedWord);
                        if (changedWord == w2) {
                            return newStack;
                        }
                        chainPaths.push(newStack);
                    }
                }
            }
        }
    }
    return stack<string>();
}

























