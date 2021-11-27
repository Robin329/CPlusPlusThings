//
// Created by renbin jiang on 2021/4/26.
//
#include <cstring>
#include <ctime>
#include <iomanip>

#include "iostream"

using namespace std;

int main(int argc, char **argv) {
    int nights = 1001;
    int *pt = new int;
    *pt = 1001;

    cout << "1.-------------------------\n";
    cout << "nights value = ";
    cout << nights << ": location " << &nights << endl;
    cout << "int ";
    cout << "value = " << *pt << ": location = " << pt << endl;
    double *pd = new double;
    *pd = 100000001.0;
    cout << "double ";
    cout << "value = " << *pd << ": location = " << pd << endl;
    cout << "location of pointer pd: " << &pd << endl;
    cout << "size of pt = " << sizeof(pt);
    cout << ": size of *pt = " << sizeof(*pt) << endl;
    cout << "size of pd = " << sizeof pd;
    cout << ": size of *pd = " << sizeof(*pd) << endl;

    cout << "2.-------------------------\n";
    double *p1 = new double[3];
    p1[1] = 0.1;
    p1[2] = 0.2;
    p1[3] = 0.3;
    cout << "3.-------------------------\n";
    char food[3] = "ro";
    strncpy(food, "jiang", strlen("jiang") > strlen(food) ? strlen(food) : strlen("jiang"));
    cout << "food:" << food << endl;
    cout << "4.-------------------------\n";
    std::time_t t = std::time(NULL);
    std::tm tm = *std::localtime(&t);
    //  std::cout.imbue(std::locale("CHS"));
    std::cout << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << '\n';
    return 0;
}