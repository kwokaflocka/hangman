//
// Created by Sally Kwok on 5/23/18.
//

#include "HangMan.h"

//Default Constructor
// Declares a string, two maps (one for storing all letter of the alphabet, one for storing
// only characters within the word the user has to guess), four sets, each holding words
// suited for the difficulty level, counter for number of guesses, and user game level choice
// set to zero
// The string is initialized to empty string (word not randomly selected yet), the alphabet map
// is inserted with the characters as keys, with all values set to bool false (no letters
// guessed yet), and the sets are initialized with the appropriate words through the function
// importWords()
// Pre: Default constructor is called in main()
// Post: one string, two maps, four set, two size_t declared, all initialized save for one map (to
//      be initialized later)
HangMan::HangMan() : hiddenWord(""), guessTheWord(), letterTracker(), easy(), medium(), hard(),
                     extreme(), guessCount(0), userPickLevel(0) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (size_t i = 0; i < alphabet.length(); i++) {
        letterTracker[alphabet[i]] = false;
    }
    importWords(WORD_DICTIONARY);
}


//importWords()
// Opens an input stream that reads from a user-defined file and sorts each string in a
// respective set depending on the number of unique characters within the word using helper
// function organizeIntoLevels()
// Pre: organizeIntoLevels() exists, four sets declared
// Post: four sets initialized with words from the user defined file base on number of unique
//      characters
void HangMan::importWords(const std::string &filename) {
    std::ifstream infile;
    infile.open(filename.c_str());
    if (infile.fail()) {
        std::invalid_argument("File could not be opened");
    }
    std::string wordToAdd;
    std::set<char> charSet;
    //creates a set filled with letters from the words imported in- then depending on size of set,
    //the word is added to a specific set (level)
    while (infile >> wordToAdd) {
        for (int i = 0; i < int(wordToAdd.length()); i++) {
            charSet.insert(wordToAdd[i]);
        }
        organizeIntoLevels(charSet.size(), wordToAdd);
        //clearing the set to check the next word
        charSet.clear();
    }
}


//organizeIntoLevels()
// Receives an int that describes the number of unique letters in a string, and the string
// itself. Inserts the string into a respective level set.
// Pre: Size(int) and string are passed by importWords(), four sets declared
// Post: One word is inserted into one set (per call)
void HangMan::organizeIntoLevels(const int &size, const std::string &word) {
    if (size >= 8) {
        extreme.insert(word);
    } else if (size >= 7) {
        hard.insert(word);
    } else if (size >= 5) {
        medium.insert(word);
    } else {
        easy.insert(word);
    }
}


//gamePrompt()
// Welcomes user to the game and prompts them to choose from 4 levels of game play. Reprompts
// if the input is not a valid level until one is entered, and returns the level (int)
// Pre: User enters value from console
// Post: Valid user-chosen level(int) is returned     CONSIDER change-  if you updatethe
// userPickLevel, should you just make a separate method that returns the value of that private data field
// to pass that value in the driver to wordselection? and make this a void function or leave as is?
size_t HangMan::gamePrompt() {
    std::cout << "Welcome to HANGMAN" << std::endl;
    std::cout << "Select Level:" << std::endl;
    std::cout << "(1) Easy\n(2) Medium\n(3) Hard\n(4) Extreme\n";
    int userChoice;
    std::cin >> userChoice;

    while (userChoice < 0 || userChoice > 4) {
        std::cout << "Please select Levels 1-4" << std::endl;
        std::cin >> userChoice;
    }
    userPickLevel = userChoice;
    return size_t(userChoice);
}


//wordSelection()
// Receives and accesses a corresponding set of words depending on the level choice chosen
// by the user and a random word is selected and returned from the selected set. Aided
// by helper function leveltoSetConvert()
// Pre: leveltoSetConvert() exists, user has selected a level of gameplay passed by
// gamePrompt()
// Post: Random string from set is returned
const std::string &HangMan::wordSelection(size_t userLevelChoice) const {
    //randNum will range depending on level chosen
    size_t randNum = rand() % size_t(levelToSetConvert(userLevelChoice).size());

    //Iterator will point to the beginning of corresponding set level, then be advanced
    //the number of times decided randomly
    Level::iterator it = (levelToSetConvert(userLevelChoice)).begin();
    std::advance(it, randNum);

    return *it;
    //hiddenWord = *(it);
    //std::cout << *it << std::endl;
    //can't do unless I overload operator
    //hiddenWord = *it;
}


//levelToSetConvert()
// Receives an int signifying game level and returns the correct set to select word from
// Pre: Sets have been filled with playable words and user has entered desired level
// Post: Desired set is returned
const Level &HangMan::levelToSetConvert(const size_t &level) const {
    if (level == 1) {
        return easy;
    } else if (level == 2) {
        return medium;
    } else if (level == 3) {
        return hard;
    } else {
        return extreme;
    }
}


//gameSetup()
// Assigns private string the value of the string selected by wordSelection() and initializes
// the empty map (guessTheWord) with the letters of the string passed as keys. All values are
// set to false.
// Pre: String has been selected for play, a map has been declared
// Post: Empty map is filled with unique characters of the passed strings as keys, all values
//      set to bool false
void HangMan::gameSetup(const std::string &str) {
    //Set string field to the actual gameplay word
    hiddenWord = str;
    //COMMENT OUT THE LINE BELOW TO STOP CHEATING:
    //std::cout << hiddenWord << std::endl;

    //Fills map with letters of from the chosen word to play as keys, sets all values to bool false
    GuessWord::iterator p1;
    for (size_t i = 0; i < hiddenWord.length(); i++) {
        if (guessTheWord.find(hiddenWord[i]) == guessTheWord.end()) {
            guessTheWord[hiddenWord[i]] = false;
        }
    }
    /* CHECK:
    for (p1 = guessTheWord.begin(); p1 != guessTheWord.end(); ++p1) {
        std::cout << (p1 -> first) << " " << (p1 -> second) << std::endl;
    }*/
}


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
void HangMan::gameOn() {
    char letterGuess;
    size_t maxGuess;

    if (userPickLevel == 1) {
        maxGuess = EASY_PLAY;
    } else if (userPickLevel == 2) {
        maxGuess = MEDIUM_PLAY;
    } else {
        maxGuess = HARDEX_PLAY;
    }

    //std::cout << "Letters Guessed: " << std::endl;
    size_t zero = 0;
    while (!gameWon() && guessCount < maxGuess) {
        //triedLetters(zero);
        std::cout << "number guess: " << guessCount << std::endl;

        std::cout << "You have " << (maxGuess - guessCount) << " guess(es) left" << std::endl;
        //triedLetters(zero);
        std::cout << "Enter a letter: " << std::endl;
        std::cout << std::endl;
        std::string empty = "";
        std::cout << gameVisual(empty) << std::endl;

        std::cin >> letterGuess;
        letterTracker[letterGuess] = true;
        triedLetters(zero);

        //letter not found in word
        if (guessTheWord.find(letterGuess) == guessTheWord.end()) {
            std::cout << "\nLetter " << letterGuess << " not found in word\n" << std::endl;
            //std::cout << "Enter another letter: " << std::endl;
        } else {
            //new letter found
            if ((guessTheWord.find(letterGuess)->second) == false) {
                std::cout << "\nLetter " << letterGuess << " found in word!\n" << std::endl;
                guessTheWord.find(letterGuess)->second = true;

                /* CHECK:
                GuessWord::iterator p1;
                for (p1 = guessTheWord.begin(); p1 != guessTheWord.end(); ++p1) {
                    std::cout << (p1 -> first) << " " << (p1 -> second) << std::endl;
                }*/

                /* CHECK:
                GuessWord::iterator p1;
                for (p1 = letterTracker.begin(); p1 != letterTracker.end(); ++p1) {
                    std::cout << (p1 -> first) << " " << (p1 -> second) << std::endl;
                }*/

                //recheck if they win after guessing the letter, if not, another prompt
            } else {
                std::cout << "\nLetter " << letterGuess << " found in word - but you've already guessed this letter :/"
                          << std::endl;
            }
        }
    }
    if (gameWon()) {
        std::cout << "You Won!!! - Your word was " << hiddenWord << std::endl;
    } else {
        std::cout << "Your word was " << hiddenWord << " - Better luck next time!"<< std::endl;
    }
}


//gameWon()
// Iterates through the map guessTheWord and returns true if all values of the key,value pairs
// are set to true
// Pre: guessTheWord map has been declared and initialized
// Post: bool value is returned - true if all map values are true, else bool false
bool HangMan::gameWon() {
    bool won = true;
    GuessWord::iterator p1;
    for (p1 = guessTheWord.begin(); p1 != guessTheWord.end() && (won == true); ++p1) {
        if ((p1->second) == false) {
            won = false;
        }
    }
    return won;
}


//gameVisual()
// Constructs a visual of the ongoing game by iterating through the guessTheWord map to
// determine if a letter of the string has been guessed. If not, a dash will be concatenated,
// else the letter itself will be.
// Pre: An empty string must be passed, guessTheWord map is initialized
// Post: A string representative of the current game is returned
const std::string& HangMan::gameVisual(std::string &build) {
    for (size_t i = 0; i < hiddenWord.length(); i++) {
        //the conditional should return the bool value since hiddenWord[i] is the direct key
        if (guessTheWord[hiddenWord[i]]) {
            build += hiddenWord[i];
        } else {
            build += "_ ";
        }
        build += " ";
    }
    return build;
}

void HangMan::triedLetters(size_t count) {
    //size_t count = 0;
    std::cout << "Letters Guessed: ";
    GuessWord::const_iterator p1;
    for (p1 = letterTracker.begin(); p1 != letterTracker.end(); ++p1) {
        if (p1->second == true) {
            std::cout << p1->first << " ";
            count++;
        }
    }
    std::cout << std::endl;
    guessCount = count;
    //return count;
}


//void HangMan::levelSize() const {
//    std::cout << "Easy: " << (easy.size()) << std::endl;
//    std::cout << "Medium: " << (medium.size()) << std::endl;
//    std::cout << "Hard: " << (hard.size()) << std::endl;
//    std::cout << "Extreme: " << (extreme.size()) << std::endl;
//}
