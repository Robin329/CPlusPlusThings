//
// Created by renbin jiang on 2022/5/12.
//
// -----------------------------------------------------------------------------
//
// C11 - Drill 10
/*
        Make a simple table including last name, first name, telephone number, and
        email address for yourself and at least five of your friends. Experiment
        with different field widths until you are satisfied that the table is presented
        well.

        ...don't forget your mother's maiden name and the 3 digits on the back of your
        credit card.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct information {
    information(double phone, string fn, string ln, string e)
          : telNumber(phone), firstName(fn), lastName(ln), email(e) {}

    double telNumber{};
    string firstName, lastName, email;
};

// -----------------------------------------------------------------------------

void printTable(const vector<information>& v) {
    for (int i = 0; i < 75; ++i) cout << "-";
    cout << endl;
    cout << '|' << setw(15) << " First Name " << '|' << setw(15) << " Last Name" << '|' << setw(25)
         << " Email Address" << '|' << setw(15) << " Phone Number" << '|' << endl;
    for (int i = 0; i < 75; ++i) cout << "-";
    cout << endl;
    for (information i : v)
        cout << '|' << setw(15) << i.firstName << '|' << setw(15) << i.lastName << '|' << setw(25)
             << i.email << '|' << setw(15) << fixed << setprecision(0) << i.telNumber << '|'
             << endl;
    for (int i = 0; i < 75; ++i) cout << "-";
}

// -----------------------------------------------------------------------------

int main() {
    vector<information> v_info = {{47123123456, "John", "Kimble", "itsnotatuma@sky.com"},
                                  {55555555555, "Jack", "Slater", "lasthero@aol.com"},
                                  {78945632123, "Douglas", "Quaid", "thechopper@hotmail.com"},
                                  {56824598645, "Howard", "Langston", "actiontoy@gmail.com"},
                                  {36984561234, "Ben", "Richards", "running4eva@email.com"}};

    printTable(v_info);

    cout << endl;
    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
