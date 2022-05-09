// -----------------------------------------------------------------------------
//
// C10 - Exercise 6
/*
    Define a Roman_int class for holding Roman numerals (as ints) with a << and >>.
    Provide Roman_int with an as_int() member that returns the int value, so that
    if r is a Roman_int, we can write
    cout << "Roman" << r << " equals " << r.as_int() << '\n';

    now does checking to see if roman numeral is correct format
    bug fix on roman_int to int - can now convert ints up to 9999 reliably
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

vector<int> num = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
vector<string> sym = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};

int returnNumber(string s) {
    for (int i = 0; i < sym.size(); ++i) {
        if (s == sym[i]) return num[i];
    }

    return -1;
}

// -----------------------------------------------------------------------------

// modified converter from
// https://www.geeksforgeeks.org/converting-decimal-number-lying-between-1-to-3999-to-roman-numerals/ this says it only
// works between 1 - 3999 however it does work up to 9999
string getRoman(int number) {
    int i = 12;
    string romanI;
    while (number > 0) {
        int div = number / num[i];
        number = number % num[i];
        while (div--) {
            romanI += sym[i];
        }
        i--;
    }

    return romanI;
}

// -----------------------------------------------------------------------------

class Roman_int {
public:
    Roman_int() {}
    ~Roman_int() {}

    int as_int();
    bool checkRoman_Int();

    friend ostream& operator<<(ostream& os, const Roman_int& ri);
    friend istream& operator>>(istream& is, Roman_int& ri);

private:
    string m_numeral;
    int m_integer;
};

// -----------------------------------------------------------------------------

int Roman_int::as_int() {
    int curNum = 0;
    int nextNum = 0;
    int runningTotal = 0;
    for (int i = 0; i < m_numeral.size(); ++i) {
        curNum = returnNumber(string(1, m_numeral[i])); // really annoying way of converting char to string
        if (i < m_numeral.size() - 1) {
            nextNum = returnNumber(string(1, m_numeral[i + 1]));
            if (nextNum != -1) {
                if (curNum < nextNum) {
                    runningTotal += nextNum - curNum;
                    ++i;
                } else
                    runningTotal += curNum;
            }
        } else
            runningTotal += curNum;
    }

    return runningTotal;
}

// -----------------------------------------------------------------------------

bool Roman_int::checkRoman_Int() {
    int count = 0;
    // the main rule of roman numerals is that you can't have more than three of the same symbols in a row
    // however, this program does not use the special characters to represent 10,000+ so M will be allowed
    // to break this rule
    for (int i = 0; i < m_numeral.size() - 1; ++i) {
        if (m_numeral[i] == m_numeral[i + 1] && m_numeral[i] != 'M')
            ++count;
        else
            count = 0;
        if (count > 2) {
            cout << "Incorrect Roman Numeral. Too many " << m_numeral[i] << "'s" << endl;
            return false;
        }
    }

    return true;
}

// -----------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Roman_int& ri) {
    return os << ri.m_numeral;
}

// -----------------------------------------------------------------------------

istream& operator>>(istream& is, Roman_int& ri) {
    bool input = false;
    while (!input) {
        is >> ri.m_numeral;
        input = ri.checkRoman_Int();
    }

    return is;
}

// -----------------------------------------------------------------------------

int main() {
    Roman_int r;

    while (cin >> r) cout << "Roman " << r << " equals " << r.as_int() << '\n';

    cout << endl;
    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
