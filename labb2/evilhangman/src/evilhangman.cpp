// This file creates an instance of a game of
// hangman where the player is meant to guess the
// word that the computer has chosen. However,
// the computer player cheats by changing the
// word that it chooses depending on the letters
// entered by the player.
//
// Created by
// Eric Nylander (eriny656)
// Samuel Blomqvist (sambl126)

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;
using WordSets = map<string, vector<string>>;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/*
 * Starts the game. Sets the parameters of how many
 * letters in the word, how many guesses the player has
 * to find the correct word, and whether or not to
 * show the dictionary  of remaining possible words.
 *
 * return: <string> the dictionary of words of the
 *          entered length
*/
vector<string> startGame();

/*
 * Asks the player to provide the number of guesses
 * they want to have.
 *
 * return: the number of desired guesses
 */
unsigned getNumberOfGuesses();

/*
 * Asks the player whether or not they want to see the
 * dictionary of remaining possible words.
 *
 * return:  boolean     true if they want to see the
 *                      dictionary
 *                      else false
 */
bool showRemainingWords();

/*
 * Shows the player the correctly guessed letters and
 * their positions, and all the letters that the player
 * has chosen.
 *
 * param:   vector<string> dictionary:
 *              contains the remaining possible words
 *              that the computer can choose from.
 * param:   vector<char> selectedCharacters:
 *              contains the characters that the player
 *              has already guessed
 * param:   unordered_set<char> alphabetLetters:
 *              a set of the letters of the alphabet
 * param:   bool showWords:
 *              true: show the set of remaining possible
 *                    words
 *              false: do not -''-
 *
 * return:  the character that the player enters
 */
char selectCharacter(vector<string> &dictionary, vector<char> &selectedCharacters, unordered_set<char> &alphabetLetters, bool showWords);

/*
 * Determines the largest set of remaining possible words
 * after the player has chosen their character. Edits the
 * dictionary of remaining possible words to contain that
 * set
 *
 * param:   vector<string> dictionary:
 *              contains the set of remaining possible
 *              words
 * param:   string guess:
 *              contains the string of correctly guessed
 *              letters of the word
 * param:   char input:
 *              contains the character that the player has
 *              chosen
 * param:   bool lastStep:
 *              true: the player has only one guess left
 *              false: the player has more than one guess
 *              left
 *
 * return:  bool:
 *              true: the player has entered as character
 *                    that must be in the selected string
 *              false: the computer has selected a set of
 *                     words that does not contain the entered
 *                     character
 */
bool isCorrectGuess(vector<string> &dictionary, string &guess, char input, bool &lastStep /*(lite elakare)*/);

/*
 * Creates the string to be used as the key in the set of
 * possible dictionaries when determining the longest set of
 * possible words.
 *
 * param:   string word:
 *              the string contining the correctly guessed
 *              characters
 * param:   string searchString:
 *              the edited string containing the word edited
 *              to contain the input character
 * param:   char input:
 *              the character that the user has entered as a
 *              guess
 */
void createWordSet(string &word, string &searchString, char input);


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
        unsigned currentStep = 0;
        bool lastStep = false;

        vector<string> dictionary = startGame();

        if(dictionary.empty()) {
            break;
        }
        for(unsigned i=0; i < dictionary[0].length(); i++) {
            guess.push_back('-');
        }
        unsigned maxStep = getNumberOfGuesses();

        bool showWords = showRemainingWords();

        while(true) {
            currentSelectedCharacter = selectCharacter(dictionary, selectedCharacters, alphabetLetters, showWords);
            if (currentSelectedCharacter == '/') continue;

            if(currentStep == maxStep-1) lastStep = true;

            if(!isCorrectGuess(dictionary, guess, currentSelectedCharacter, lastStep)){
                ++currentStep;
            }

            cout << "Progress:" << endl << guess << endl;
            cout << "You have " << maxStep - currentStep << " guesses left!" << endl << endl;

            if(guess.find('-') == string::npos) {
                cout << "You won the game!!" << endl;
                cout << "Would you like to play again? Press 'a' to start and 'q' to quit!" << endl;
                break;
            }
            if(currentStep >= maxStep) {
                // Player lose the game
                cout << "You lost the game!" << endl;
                cout << "Would you like to play again? Press 'a' to start and 'q' to quit!" << endl;
                break;
            }
        }
    }
    cout << "Thanks for playing!" << endl;
    return 0;
}

vector<string> startGame() {
    vector<string> dictionary;
    string word;
    ifstream dicStream;

    string input;

    cin >> input;

    if(input=="a") {
        cout << endl << "Nice input xD " << input << endl << endl;
        // Find word and start game

        vector<string> tempDict;
        dicStream.open("dictionary.txt");
        while(dicStream >> word){
            tempDict.push_back(word);
        }
        unsigned strLength;

        cout << "How long would you like the word to be?" << endl << endl;

        while(true){
            cin >> strLength;

            for(string word: tempDict){
                if(word.length() == strLength){
                    dictionary.push_back(word);
                }
            }
            if(!dictionary.empty()) break;

            cout << "I dont know any words that long!! Please enter another word length!" << endl << endl;
        }
        return dictionary;
    }
    else if(input=="q") {
        // Quit the game
        return dictionary;
    }
    cout << "Could not recognize the input, please try again!" << endl;
    return startGame();
}

unsigned getNumberOfGuesses(){
    unsigned numberOfGuesses;
    cout << "How many guesses would you like?" << endl;
    cout << "Hint: you don't need more than 26!" << endl << endl;

    cin >> numberOfGuesses;
    if(numberOfGuesses < 26){
        return numberOfGuesses;
    }

    else{
        while(numberOfGuesses >= 26){
            cout << "Please enter a number that is 26 or lower!" << endl << endl;
            cin >> numberOfGuesses;
        }
        return numberOfGuesses;
    }
}

bool showRemainingWords(){
    char input;
    cout << "Would you like to see the words that still match your guess? (y) (n)" << endl << endl;
    cin >> input;
    if(input=='y'){
        return true;
    }
    else if(input=='n'){
        return false;
    }
    else{
        return showRemainingWords();
    }
}

char selectCharacter(vector<string> &dictionary, vector<char> &selectedCharacters, unordered_set<char> &alphabetLetters, bool showWords){
    if(showWords){
        for(auto i = dictionary.begin(); i < dictionary.end(); ++i) {
            cout << *i << ", ";
        }
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

/*
 * Möjliga utökningar:
 *  1. Om en gissning ger fler bokstäver till ordet ska den vägas mindre
 *  2. Om ett ord i en möjlig dictionary (som är i mängden av alla möjliga dictionaries)
 *      Innehåller många dubbla/flera bokstäver ska den vägas mer/mindre än andra ord.
 */
bool isCorrectGuess(vector<string> &dictionary, string &guess, char input, bool &lastStep /*(lite elakare)*/) {
    string biggestSearchString;
    WordSets wordSets;
    unsigned biggestLength = 0;
    string searchString;
    vector<string> *tempVec;
    string nullString;

    for(unsigned i=0; i<guess.length(); ++i){
        nullString.push_back('-');
    }

    // guess = "----"    input = "a"
    // Create new search string that matches the "a"s in each word in the dictionary
    for(string word:dictionary) {
        searchString.clear(); // Moved out
        createWordSet(word, searchString, input);

        tempVec = &wordSets[searchString];
        tempVec->push_back(word);
        // tempVec.clear(); // Moved out
        // insertMapVector(wordSets, searchString, biggestLength, word, biggestWordSet, biggestSearchString, tempVec);
    }

    for(auto i=wordSets.begin(); i!=wordSets.end();++i){
        // uncomment for "Lite elakare"
        /*
        if(lastStep){
            string guessKey = i->first;
            if(guessKey == nullString){
                dictionary = i->second;
                return false;
            }
        }
        */
        vector<string> tmp = i->second;
        unsigned tmpLength = tmp.size();
        if(tmpLength > biggestLength){
            dictionary = tmp;
            biggestLength = tmpLength;
            biggestSearchString = i->first;
        }
    }

    for(unsigned i = 0; i < guess.length(); ++i) {
        if(biggestSearchString.at(i) != '-') {
            guess.at(i) = biggestSearchString.at(i);
        }
    }
    if(biggestSearchString!=nullString){
        return true;
    }
    return false;
}

void createWordSet(string &word, string &searchString, char input) {
    for(char character:word) {
        if(character == input) {
            searchString.push_back(character);
        }
        else{
            searchString.push_back('-');
        }
    }
}


