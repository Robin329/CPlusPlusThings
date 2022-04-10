//
// Created by renbin jiang on 2022/4/10.
//
#include "std_lib_facilities.h"

int main() {
    cout << "Please input your first name:\n";
    string first_name;
    cin >> first_name;
    cout << "Hello, " << first_name << endl;
    cout << "Enter the name of the person you want to write to\n";
    cin >> first_name;
    cout << "Dear " << first_name << "," << endl;
    cout << "   How are you doing? What is normal life like for you?\n"
         << "I saw the pictures of your wedding and it was nice to\n"
         << "remember such a wonderful day.\n";
    cout << "Please enter the name of someone you both know:\n";
    string friendName;
    cin >> friendName;
    cout << "Have you heard from " << friendName << " lately?\n";

    // 4
    char friend_sex{0};
    cout << "Is this friend a male or a female??[1:m/0:f]\n";
    cin >> friend_sex;
    cout << "if you see " << friendName << ", please ask " << (friend_sex ? "him" : "her")
         << " to call me" << endl;

    // 5
    int age;
    cout << "How old is " << first_name << "?\n";
    cin >> age;
    if (age <= 0) simple_error("you're kidding!");
    if (age > 110) simple_error("you're kidding!");

    // 6
    if (age < 12) cout << "Next year you will be " << age + 1 << ".\n";
    if (age == 17) cout << "Next year you will be able to vote!\n";
    if (age > 70) cout << "I hope you are enjoying retirement.\n";
    // 7
    cout << "Yours sincerely,\n\n\nChris Schick\n";
    return 0;
}