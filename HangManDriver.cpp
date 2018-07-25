#include "HangMan.h"

int main() {
    //seeding the random generator
    std::srand(time(0));
    HangMan Game;

    //testing
    //Game.levelSize();

    Game.gameSetup(Game.wordSelection(Game.gamePrompt()));
    Game.gameOn();


}

//improvements:

//add a hint version? --- give a letter away if too many letters wrong in a row?

//add Play again option

//add a count of letters guessed, and accompanying "hang man" picture?

//add another map to double check that a letter has been used --- hard to play otherwise

//revamp the general game--- choose the word selectively based on letter frequency and repetition?
//difficulty = summation of (frequency of unique letter * frequency in appearance in english language)
// smaller the number, harder the difficulty

// how do I sort the list then? should I make a second .cpp and .h that does the preliminary re-sorting
// of any list of word it may recieve, and then that subsequent list is the one split into difficulties?
// Or is there easier way lol?
