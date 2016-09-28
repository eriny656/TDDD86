#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <unordered_set>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

vector<string> startGame(unsigned strLength);
char selectCharacter(vector<string> &dictionary, vector<char> &selectedCharacters, unordered_set<char> &alphabetLetters);
void step(vector<string> &dictionary, string &guess, char &input);
void getGuess(string &word, string &searchString, char &input);
void insertMapVector(vector<string> &tempVec, map<string, vector<string>> &wordSets, string &searchString, unsigned &biggestLength, string &word);


int main() {
    unordered_set<char> alphabetLetters;

    for(char letter: ALPHABET){
        alphabetLetters.insert(letter);
    }

    cout << "Welcome to Hangman." << endl;
    cout << "Press 'a' to start playing! Press 'q' to quit!" << endl;

    while(true){
        vector<char> selectedCharacters;
        char currentSelectedCharacter;
        string guess;
        vector<string> dictionary;
        unsigned strLength = 5;
        unsigned currentStep = 0;
        unsigned maxStep = 15;

        for(unsigned i=0; i < strLength; i++) {
            guess.push_back('-');
        }
        if((dictionary = startGame(strLength)).empty()) {
            break;
        }

        while(true) {
            while((currentSelectedCharacter = selectCharacter(dictionary, selectedCharacters, alphabetLetters)) == '/') continue;

            step(dictionary, guess, currentSelectedCharacter);

            cout << "Progress:" << endl << guess << endl;
            ++currentStep;
            cout << "Current step is " << currentStep << " out of " << maxStep << endl;

            if(currentStep > maxStep) {
                // Player lose the game
                cout << "You lost the game!" << endl;
                cout << "Would you like to play again? Press 'a' to start and 'q' to quit!" << endl;
                break;
            }
            cout << "MEEEEEEMES " << guess.find('-') << " " << guess << endl << endl;
            if(guess.find('-') == string::npos) {
                cout << "You won the game!!" << endl;
                cout << "Would you like to play again? Press 'a' to start and 'q' to quit!" << endl;
                break;
            }
        }
    }
    cout << "Thanks for playing!" << endl;
    return 0;
}

vector<string> startGame(unsigned strLength) {
    vector<string> dictionary;
    string word;
    ifstream dicStream;

    string input;
    cin >> input;

    if(input=="a") {
        cout << "Nice input xD " << input << endl << endl;
        // Find word and start game
        dicStream.open("dictionary.txt");
        while(getline(dicStream, word)) {
            if(word.length() == strLength) {
                dictionary.push_back(word);
            }
        }
        return dictionary;
    }
    else if(input=="q") {
        cout << "Bad input xD " << input << endl << endl;
        // Quit the game
        return dictionary;
    }
    cout << "Could not recognize the input, please try again!" << endl;
    return startGame(strLength);
}

char selectCharacter(vector<string> &dictionary, vector<char> &selectedCharacters, unordered_set<char> &alphabetLetters){
    for(auto i = dictionary.begin(); i < dictionary.end(); ++i) {
        cout << *i << ", ";
    }

    char input;

    if(!selectedCharacters.empty()){
        cout << endl << endl <<  "You have guessed:" << endl;
        for(auto i = selectedCharacters.begin(); i < selectedCharacters.end(); ++i){
            cout << *i << ", ";
        }
        cout << endl << endl;
    }

    cout << "Guess a character ;)" << endl;
    cin >> input;

    if(alphabetLetters.find(input) == alphabetLetters.end()){
        cout << "You must enter a valid letter of the alphabet!" << endl;
        return '/';
    }

    for(char character: selectedCharacters){
        if(input == character){
            cout << "You have already entered this character!" << endl;
            return '/';
        }
    }

    selectedCharacters.push_back(input);
    return input;
}

void step(vector<string> &dictionary, string &guess, char &input) {
    map<string, vector<string>> wordSets;
    unsigned biggestLength = 0;
    string searchString;
    vector<string> tempVec;




    // guess = "----"    input = "a"
    // Create new search string that matches the "a"s in each word in the dictionary
    for(string word:dictionary) {
        searchString.clear(); // Moved out
        getGuess(word, searchString, input);

        tempVec.clear(); // Moved out
        insertMapVector(tempVec, wordSets, searchString, biggestLength, word);
    }

    dictionary = wordSets.begin()->second;

    string c1 = wordSets.begin()->first;
    for(unsigned i = 0; i < guess.length(); ++i) {
        if(c1.at(i) != '-') {
            guess.at(i) = c1.at(i);
        }
        cout << guess << endl;
    }
}

void getGuess(string &word, string &searchString, char &input) {
    for(char character:word) {
        if(character == input) {
            searchString.push_back(character);
        }
        else{
            searchString.push_back('-');
        }
    }
}

void insertMapVector(vector<string> &tempVec, map<string, vector<string>> &wordSets, string &searchString, unsigned &biggestLength, string &word) {
    // searchString == key,
    // We check if there is a vector in wordSets with a key that matches our searchString.
    map<string, vector<string>>::iterator ourIterator = wordSets.find(searchString);

    if (ourIterator != wordSets.end() ) {
        tempVec = ourIterator->second;
    }
    tempVec.push_back(word);
    wordSets.erase(searchString);
    if(tempVec.size() > biggestLength){
        biggestLength = tempVec.size();
        wordSets.insert(wordSets.begin(), pair<string, vector<string>> (searchString, tempVec));

        //wordSets.emplace/*_hint*/(/*wordSets.begin(), */searchString, tempVec);
    }
    else {
        wordSets.insert(wordSets.end(), pair<string, vector<string>> (searchString, tempVec));
        //wordSets.emplace/*_hint*/(/*wordSets.end(), */searchString, tempVec);
    }
}


