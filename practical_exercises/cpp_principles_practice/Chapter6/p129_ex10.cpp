//
// Created by renbin jiang on 2022/4/23.
//
//--------------------------------------------//
// C6 - Exercise 10
// this program should have error checking...but it doesn't beyond basic checking
// ...because time constraints
// also, this program does not allow for repetition in permutations as that requires
// a different formula than given in the book
//--------------------------------------------//

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------
/*
Permutations or Combinations
>> answer

if (answer == Permutation)
        calculatePermutation()
        print

else if (answer == Combination)
        calculateCombination()
        print

Repeat or Quit

--variable naming--
possibleValues = i.e 60 possible numbers to choose from for one choice
choiceAmount = i.e 3 different numbers needed for a combination
*/

// -----------------------------------------------------------------------------

double getFactorial(int possiblevalues) {
    if (possiblevalues == 0)
        possiblevalues = 1; // to prevent division by 0
    else if (possiblevalues < 0)
        possiblevalues *= -1; // flip value to a positive

    double factorial = possiblevalues;
    for (int i = factorial - 1; i > 1; --i) factorial *= i;

    return factorial;
}

// -----------------------------------------------------------------------------

// order matters
double calculatePermutation(int possiblevalues, int choiceAmount) {
    double perm = getFactorial(possiblevalues) / getFactorial(possiblevalues - choiceAmount);
    return perm;
}

// -----------------------------------------------------------------------------

// order doesn't matter
double calculateCombination(int possiblevalues, int choiceAmount) {
    double comb = calculatePermutation(possiblevalues, choiceAmount) / getFactorial(choiceAmount);
    return comb;
}

// -----------------------------------------------------------------------------

int main() {
    char decision, quit('n');
    int possiblevalues, choiceAmount;

    while (quit == 'n') {
        cout << "Would you like to calculate a combination or permutation? c/p >> ";
        cin >> decision;
        cout << "How many possible values are there? >> ";
        cin >> possiblevalues;
        cout << "How choices do you want? >> ";
        cin >> choiceAmount;

        switch (decision) {
            case 'c':
                cout << "Number of Combinations >> "
                     << calculateCombination(possiblevalues, choiceAmount) << endl;
                break;
            case 'p':
                cout << "Number of Permutations >> "
                     << calculatePermutation(possiblevalues, choiceAmount) << endl;
                break;
            default:
                cout << "Unrecognised command" << endl;
                break;
        }

        cout << "Quit? y/n >> ";
        cin >> quit;
        while (quit != 'y' || quit != 'n') {
            cout << "Unrecognised. Try again. >> ";
            cin >> quit;
        }
    }

    keep_window_open();
    return 0;
}

//------------------------------------------------------------------------------
