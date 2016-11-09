// This file takes two words as parameters and
// finds the shortest chain of words with a single
// edited letter between the two.

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
stack<string> wordChain(string, string);

int main() {
    string input;
    string output;
    string startWord;
    string endWord;
    stack<string> chain;

    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    getline(cin, input);


    startWord = input.substr(0, input.find(" "));
    endWord = input.substr(input.find(" ")+1, startWord.length()+1);

    chain = wordChain(startWord, endWord);
    while (!chain.empty()) {
        output.append(chain.top());
        chain.pop();
        output.append(", ");
    }
    cout << "Chain from " << endWord << " back to " <<  startWord << ":" << endl;
    cout << output << endl << "Have a nice day." << endl;


    // TODO: Finish the program!

    return 0;
}

stack<string> wordChain(string w1, string w2) {
    queue<stack<string>> chainPaths;
    stack<string> path;
    string word;
    unordered_set<string> dictionary;
    ifstream dicStream;
    unordered_set<string> chainedWords;
    dicStream.open("dictionary.txt");

    while(getline(dicStream, word)) {
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

        if(!tempStack.empty()){
            string secondToLast = tempStack.top();
            for(unsigned int i = 0; i < tempWord.length(); ++i) {
                if(tempWord[i] != secondToLast[i]){
                    checkedLetter = i;
                    break;
                }
            }
        }

        for (unsigned int iWord = 0; iWord < tempWord.length(); ++iWord) {
            if(iWord == checkedLetter){
                continue;
            }


            for (char alphabetLetter:ALPHABET) {
                if (tempWord[iWord] == alphabetLetter){
                    continue;
                }
                string changedWord = tempWord;
                changedWord[iWord] = alphabetLetter;
                if (dictionary.find(changedWord) != dictionary.end()) {
                    // cout << "WE FOUND SOMETHING : " << changedWord << endl;
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
    cout << "Crash xD" << endl;
}

























