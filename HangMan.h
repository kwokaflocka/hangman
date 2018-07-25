// Created by Sally Kwok on 5/23/18.
// HANGMAN (v1)

#ifndef HANGMAN_HANGMAN_H
#define HANGMAN_HANGMAN_H

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>

//multipliers
const size_t EASY_PLAY = 25;    //need 5 right - can get 16 wrong
const size_t MEDIUM_PLAY = 20;  //need 6 right - can get 9 wrong
const size_t HARDEX_PLAY = 15;    //need 7 right - can get 7 wrong  //need 8 right - can get 6 wrong



const std::string WORD_DICTIONARY = "ospd.txt";

typedef std::set<std::string> Level;
typedef std::map<char, bool> GuessWord;

class HangMan {

private:
    //Level freePlay;

    //word that player is supposed to guess
    std::string hiddenWord;
    //stores letters of the words player has to guess
    GuessWord guessTheWord;
    //make another map to hold all letters guessed already --- is there a way to meld that with the first map?
    GuessWord letterTracker; /// would it be better to just make this a string
    Level easy;
    Level medium;
    Level hard;
    Level extreme;
    size_t guessCount;
    size_t userPickLevel;

public:

    //Default Constructor
    // Declares a string, two maps (one for storing all letter of the alphabet, one for storing
    // only characters within the word the user has to guess), and four sets, each holding words
    // suited for the difficulty level.
    // The string is initialized to empty string (word not randomly selected yet), the alphabet map
    // is inserted with the characters as keys, with all values set to bool false (no letters
    // guessed yet), and the sets are initialized with the appropriate words through the function
    // importWords()
    // Pre: Default constructor is called in main()
    // Post: one string, two maps, and four set declared, all initialized save for one map (to
    //      be initialized later)
    HangMan();

    //importWords()
    // Opens an input stream that reads from a user-defined file and sorts each string in a
    // respective set depending on the number of unique characters within the word using helper
    // function organizeIntoLevels()
    // Pre: organizeIntoLevels() exists, four sets declared
    // Post: four sets initialized with words from the user defined file base on number of unique
    //      characters
    void importWords(const std::string &filename);

    //organizeIntoLevels()
    // Receives an int that describes the number of unique letters in a string, and the string
    // itself. Inserts the string into a respective level set.
    // Pre: Size(int) and string are passed by importWords(), four sets declared
    // Post: One word is inserted into one set (per call)
    void organizeIntoLevels(const int &size, const std::string &word);

    //gamePrompt()
    // Welcomes user to the game and prompts them to choose from 4 levels of game play. Reprompts
    // if the input is not a valid level until one is entered, and returns the level (int)
    // Pre: User enters value from console
    // Post: Valid user-chosen level(int) is returned
    size_t gamePrompt();

    //wordSelection()
    // Receives and accesses a corresponding set of words depending on the level choice chosen
    // by the user and a random word is selected and returned from the selected set. Aided
    // by helper function leveltoSetConvert()
    // Pre: leveltoSetConvert() exists, user has selected a level of gameplay passed by
    // gamePrompt()
    // Post: Random string from set is returned
    const std::string &wordSelection(size_t userLevelChoice) const;

    //levelToSetConvert()
    // Receives an int signifying game level and returns the correct set to select word from
    // Pre: Sets have been filled with playable words and user has entered desired level
    // Post: Desired set is returned
    const Level &levelToSetConvert(const size_t &level) const;

    //gameSetup()
    // Assigns private string the value of the string selected by wordSelection() and initializes
    // the empty map (guessTheWord) with the letters of the string passed as keys. All values are
    // set to false.
    // Pre: String has been selected for play, a map has been declared
    // Post: Empty map is filled with unique characters of the passed strings as keys, all values
    //      set to bool false
    void gameSetup(const std::string &str);

    //gameOn()
    // Prints to console a prompt to enter letter and a simple game visualization through helper
    // function gameVisual(). Once a letter has been guessed, it will update the
    // letterTracker map (flipping the char key to point to a bool true) and print to console all
    // the letters that have been guessed already. If the letter is also a letter that exists in
    // the word to guess, it will also turn the value associated with char key to true. It will
    // continue to prompt for letters until all the values in the guessTheWord map are true, where
    // it will announce the user has won.
    // Pre: hiddenWord initialized with a valid string to play, letterTracker map has all letters
    //      of the alphabet serving as keys with all values set to bool false, guessTheWord map
    //      consists of key,value pairs with keys from letters of the string to guess, and values
    //      set to bool false
    // Post: All values in the map guessTheWord are now bool true; minimally, all identical char
    //       keys in letterTracker should also be bool true, ends game (won)
    void gameOn();

    //gameWon()
    // Iterates through the map guessTheWord and returns true if all values of the key,value pairs
    // are set to true
    // Pre: guessTheWord map has been declared and initialized
    // Post: bool value is returned - true if all map values are true, else bool false
    bool gameWon();   ///why cant const!!!!! :(((((

    //gameVisual()
    // Constructs a visual of the ongoing game by iterating through the guessTheWord map to
    // determine if a letter of the string has been guessed. If not, a dash will be concatenated,
    // else the letter itself will be.
    // Pre: An empty string must be passed, guessTheWord map is initialized
    // Post: A string representative of the current game is returned
    const std::string &gameVisual(std::string &build);

    void triedLetters(size_t count);


    //void selectGameLevel(size_t playLevel);
    //bool checkLetter(const char &userLetter) const;


    //Test Methods:
    //void levelSize() const;


};
#endif //HANGMAN_HANGMAN_H
