#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
vector<string> startGame(int strLength);
bool step(vector<string> &dictionary, string &guess);
void chooseNewWordSet(vector<string> &dictionary, char &input, string &guess);

int main() {
    int strLength = 5;
    int currentStep;
    int maxStep;

    vector<string> dictionary;

    cout << "Welcome to Hangman." << endl;
    cout << "Press 'a' to start playing! Press 'q' to quit!" << endl;

    while(true){
        currentStep = 0;
        maxStep = 15;
        string guess;
        for(int i=0; i < strLength; i++) {
            guess.push_back('-');
        }
        dictionary = startGame(strLength);
        if(dictionary.empty()) {
            break;
        }
        while(step(dictionary, guess)) {
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

vector<string> startGame(int strLength) {
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

bool step(vector<string> &dictionary, string &guess) {
    char input;

    for(auto i = dictionary.begin(); i < dictionary.end(); ++i) {
        cout << *i << ", ";
    }
    cout << "Guess a character ;)" << endl;


    // TODO: Check so we dont check the same letter again!! List?

    cin >> input;
    for(char alphabetLetter:ALPHABET) {
        if (input == alphabetLetter){
            chooseNewWordSet(dictionary, input, guess);
            return true;
        }
    }
    cout << "Invalid input!" << endl;
    return true;
}

void chooseNewWordSet(vector<string> &dictionary, char &input, string &guess) {
    map<string, vector<string>> wordSets;
    int biggestLength = 0;
    string searchString;
    vector<string> tempVec;

    // guess = "----"    input = "a"
    // Create new search string that matches the "a"s in each word in the dictionary
    for(string word:dictionary) {
        searchString.clear(); // Moved out
        for(char character:word) {

            if(character == input) {
                searchString.push_back(character);
            }
            else{
                searchString.push_back('-');
            }
        }

        // searchString == key,
        // We check if there is a vector in wordSets with a key that matches our searchString.
        tempVec.clear(); // Moved out
        if (wordSets.find(searchString) != wordSets.end() ) {
            tempVec = wordSets.at(searchString);
        }
        tempVec.push_back(word);
        wordSets.erase(searchString);
        if(tempVec.size() > biggestLength){
            biggestLength = tempVec.size();
            wordSets.emplace_hint(wordSets.begin(), searchString, tempVec);
        }
        else {
            wordSets.emplace_hint(wordSets.end(), searchString, tempVec);
        }
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
