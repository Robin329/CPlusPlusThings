//
// Created by renbin jiang on 2022/4/23.
//
//--------------------------------------------//
// C6 - Exercise 8
//--------------------------------------------//

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------
vector<char> answers(4);
vector<char> guesses(4);

void resetGame() {
    vector<char> choices;
    // populate choices with ascii lowercase letters from 97-122 (a-z)
    for (char i = 'a'; i <= 'z'; ++i) choices.push_back(i);

    cout << "Enter a number, any number >> ";
    int seed(0);
    cin >> seed;
    seed_randint(seed);
    cout << "seed:" << seed << endl;

    // populate with random chars (no repeats)
    for (int i = 0; i < answers.size(); ++i) {
        int index = randint(choices.size() - 1);
        cout << "index:" << index << endl;
        answers[i] = choices[index];
        // delete from choices so it can't be chosen again to prevent repeats
        choices.erase(choices.begin() + index);
    }
}

// -----------------------------------------------------------------------------

int main() {
    resetGame();

    cout << "Bulls & Cows" << endl;
    cout << "Rules: You need to correctly guess the 4 letter sequence." << endl;
    cout << "Bull - Getting a letter right in the right place." << endl;
    cout << "Cow - Getting a letter right in the wrong place." << endl;

    char guess;
    bool gameWon = false;

    while (!gameWon) {
        cout << "\nGuess (a-z, no repeats) >> ";
        for (int i = 0; i < guesses.size(); ++i) cin >> guesses[i];

        // loop through guesses
        for (int i = 0; i < guesses.size(); ++i) {
            // loop through answers
            for (int n = 0; n < answers.size(); ++n) {
                if (i == n) {
                    if (guesses[i] == answers[n]) cout << "1 Bull, ";
                } else {
                    if (guesses[i] == answers[n]) cout << "1 Cow, ";
                }
            }
        }

        // they guesses all the digits
        if (guesses == answers) {
            cout << "**Incredible job!**" << endl;
            gameWon = true;
            cout << "Would you like to play again? y/n >> ";
            char yn;
            cin >> yn;
            if (yn == 'y') {
                resetGame();
                gameWon = false;
            }
        } else
            cout << "\nHmmm, not quite, try again.\n";
    }

    keep_window_open();
    return 0;
}

//------------------------------------------------------------------------------
