//
// Created by renbin jiang on 2022/5/12.
//
// -----------------------------------------------------------------------------
// C11 - Drills 1, 2, 3, 4, 5, 6, 7, 8
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

inline ios_base &general(ios_base &b) {
    b.setf(ios_base::fmtflags(0), ios_base::floatfield);
    return b;
}

int main() {
    /*
    Drill 1
    -Start a program called Test_output.cpp. Declare an integer birth_year and
    assign it the year you were born.
    */
    int birth_year = 1875;

    /*
    Drill 2
    -Output your birth_year in decimal, hexadecimal, and octal form.
    Drill 3
    -Label each value with the name of the base used.
    Drill 4
    -Line up the output columns using tab.
    */
    cout << "Decimal:\t" << showbase << dec << birth_year << endl;
    cout << "Hexadecimal:\t" << showbase << hex << birth_year << endl;
    cout << "Octal:\t\t" << showbase << oct << birth_year << endl;
    // cout << noshowbase;

    /*
    Drill 5
    -Now output your age.
    Drill 6
    -Fix your output to decimal
    */
    cout.unsetf(std::ios::oct);
    cout << "My Age:\t\t" << 145 << endl;

    /*
    Drill 7
    -Show the base for your birth_year in Drill 2
    Drill 8
    -Try reading as octal, hexadecimal etc. Run the code and explain the results
    */
    int a{}, b{}, c{}, d{};
    cout << "Please input 4 numbers:\n";
    //    cin >> a >> oct >> b >> hex >> c >> d;
    cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';
    // the numbers are being converted to decimal as the default is decimal

    cout << "-------------------------" << endl;
    cout << 1234.56789 << "\t\t(general)\n"
         << fixed << 1234.56789 << "\t(fixed)\n"
         << scientific << 1234.56789 << "\t(scientific)\n";

    cout << "-------------------------" << endl;
    cout << 1234.56789 << "\t\t(general)\n" << general << 1234.56789 << "\t(general)\n";

    cout << "-------------------------" << endl;
    const float f = 1234567.89;
    cout << "Standard:\t" << f << endl;
    cout << "DefaultFloat:\t" << defaultfloat << f << endl;
    cout << "Fixed:\t\t" << fixed << f << endl;
    cout << "Scientific:\t" << scientific << f << endl;
    cout << endl;

    const double d1 = 1234567.89;
    cout << "Standard:\t" << d1 << endl;
    cout << "DefaultFloat:\t" << defaultfloat << d1 << endl;
    cout << "Fixed:\t\t" << fixed << d1 << endl;
    cout << "Scientific:\t" << scientific << d1 << endl;
    cout << endl;

    cout << "Standard:\t" << 1234567.89 << endl;
    cout << "DefaultFloat:\t" << defaultfloat << 1234567.89 << endl;
    cout << "Fixed:\t\t" << fixed << 1234567.89 << endl;
    cout << "Scientific:\t" << scientific << 1234567.89 << endl;
    cout << endl;

    /*
            Fixed is the most accurate for double and cout due to it's amount of
            precision after the decimal point. It is important to
            note that float does not have the same degree of precision as the
            others regardless.
    */

    cout << "-------------------------" << endl;

    cout << "-------------------------" << endl;

    cout << "-------------------------" << endl;

    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
