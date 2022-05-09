// -----------------------------------------------------------------------------
//
// C10 - Exercise 5
//
/* Write the function print_year() mentioned in section 10.11.2

    I'm assuming that it's expected that this will not work
  *sometime later*
  I decided to make it work.
*/
// -----------------------------------------------------------------------------

//--INCLUDES--//
#include "std_lib_facilities.h"

const int notAReading = -7777; // less than absolute zero (kelvin)
const int notAMonth = -1;
vector<string> month_input_tbl = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};

// -----------------------------------------------------------------------------

string month_to_string(int i) {
    if (i < 0 || 12 <= i) return "-1";
    return month_input_tbl[i];
}

// -----------------------------------------------------------------------------

struct Day {
    // create vector of size 24, each initialised to notAReading
    vector<double> hour{vector<double>(24, notAReading)};
};

// -----------------------------------------------------------------------------

struct Month {
    int month = notAMonth; // 0 - 11. Jan is 0
    vector<Day> day{32};   // 1 - 31. One vector of readings per day. [0] wasted to keep code simple
};

// -----------------------------------------------------------------------------

struct Year {
    int year;
    vector<Month> month{12}; // 0 -11. Jan is 0
};

// -----------------------------------------------------------------------------

// format is: (I'm going to ignore the weird spacing/lines. I assume that's just due
// to printing issues)
/*
    { year 1990 }
    {year 1991 { month jun }} -- this one won't print as if the month is empty then it will be assigned as "not a month"
    { year 1992 { month jan ( 1 0 61.5) } {month feb (1 1 64) (2 2 65.2) } }
    {year 2000
        { month feb (1 1 68 ) (2 3 66.66 ) ( 1 0 67.2)}
        {month dec (15 15 -9.2) (15 14 -8.8) (14 0 -2) }
    }
*/
// this is horrible and I hate everything about this exercise
ofstream& print_year(ofstream& ost, const Year& y) {
    ost << "{ year " << y.year;

    if (y.month.empty())
        ost << " } ";
    else {
        for (uint32_t i = 0; i < y.month.size(); ++i) {
            if (y.month[i].month != notAMonth) {
                ost << " { month " << month_to_string(y.month[i].month);
                for (uint32_t j = 0; j < y.month[i].day.size(); ++j) // this is disgusting
                {
                    for (uint32_t h = 0; h < y.month[i].day[j].hour.size(); ++h) // this is horrifying
                    {
                        if (y.month[i].day[j].hour[h] != notAReading) {
                            ost << " (" << i << " " << h << " " << y.month[i].day[j].hour[h] << ")";
                        }
                    }
                }
                ost << " }";
            }
        }
    }
    ost << " } ";
    ost.close();
    return ost;
}

// -----------------------------------------------------------------------------

int main() {
    // ok I have to make this work somehow so I can test it; it's driving me nuts
    Day day1, day2;
    Month jan, feb;
    Year year2018;

    day1.hour[0] = 20.3;
    day1.hour[1] = 21.3;
    day2.hour[10] = 20.3;
    day2.hour[11] = 21.3;

    jan.month = 0;
    jan.day[1] = day1;
    jan.day[2] = day2;
    feb.month = 1;
    feb.day[1] = day1;
    feb.day[2] = day2;

    year2018.year = 2018;
    year2018.month[0] = jan;
    year2018.month[1] = feb;

    ofstream horribleFile(
            FileSystem::getPath("practical_exercises/cpp_principles_practice/Chapter10/res/disgustingtemps.txt")
                    .c_str());
    print_year(horribleFile, year2018);

    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
