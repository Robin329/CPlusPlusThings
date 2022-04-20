//
// Created by renbin jiang on 2022/4/18.
//
#include <gtest/gtest.h>

#include "std_lib_facilities.h"

int area(int length, int width)
// calculate area of a rectangle
// pre-conditions: length and width are positive
// post-condition: returns a positive value that is area
{
    if (length <= 0 || width <= 0) error("area() pre-condition");
    int a = length * width;
    if (a <= 0) error("area() post-condition");
    return a;
}

TEST(errors, Error1) {
    try {
        // This is an example of the area function with pre & post conditionals
        cout << "Area: " << area(-1, 2) << '\n';
    } catch (exception& e) {
        cerr << "error: " << e.what() << '\n';
    } catch (...) {
        cerr << "Oops: unknown exception!\n";
    }
}

TEST(errors, Errors2) {
    try {
        // This is an example of the area function with pre & post conditionals
        cout << "Area: " << area(-1.2, -2) << '\n';
    } catch (exception& e) {
        cerr << "error: " << e.what() << '\n';
    } catch (...) {
        cerr << "Oops: unknown exception!\n";
    }
}

TEST(errors, Err_p89) {
    vector<double> temps;

    temps.push_back(-16.5);
    temps.push_back(-23.2);
    temps.push_back(-24.0);
    temps.push_back(-25.5);
    temps.push_back(7.5);
    temps.push_back(16.5);

    double sum = 0;
    double high_temp = 0; // zero init may affect assignment
    double low_temp = 0;  // zero init may affect assignment

    for (int x : temps) {
        if (high_temp == 0 && low_temp == 0) {
            high_temp = x;
            low_temp = x;
        }

        if (x > high_temp) high_temp = x; // find high
        if (x < low_temp) low_temp = x;   // find low
        sum += x;
    }

    cout << "High temperature: " << high_temp << '\n';
    cout << "Low temperature: " << low_temp << '\n';
    cout << "Average temperature: " << sum / temps.size() << '\n';
}

double ctok(double c) // converts Celsius to Kelvin
{
    constexpr double k_conversion = 273.15;

    double k = c + k_conversion;
    return k;
}

TEST(Codeoptimization, p2) {
    double c = 0;              // declare input variable
    c = 12.0;                  // retrieve temperature to input variable
    double k = ctok(c);        // convert temperature
    cout << "K:" << k << '\n'; // print out temperature
    k = ctok(-11.0);
    cout << "K:" << k << '\n';
}