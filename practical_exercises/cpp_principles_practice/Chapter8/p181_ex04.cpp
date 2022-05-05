//
// Created by renbin jiang on 2022/5/6.
//
// -----------------------------------------------------------------------------
//
//	C8 - Exercise 5
//
// -----------------------------------------------------------------------------

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void print(const vector<int>& v, const string& label) {
    cout << label << endl;
    // for every int in vector, print that int
    for (int i : v) cout << i << endl;
}

// -----------------------------------------------------------------------------

vector<int> reverseVectorNew(vector<int> v) {
    vector<int> temp;
    for (int i = v.size() - 1; i >= 0; --i) temp.push_back(v[i]);

    return temp;
}

// -----------------------------------------------------------------------------

void reverseVectorRef(vector<int>& v) {
    for (int i = 0; i < (v.size() / 2); ++i) swap(v[i], v[v.size() - (i + 1)]);
}

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------

void print(const vector<string>& v, const string& label)
{
    cout << label << endl;
    //for every int in vector, print that int
    for (string i : v)
        cout << i << endl;
    
    cout << "// -----------------------------------------------------------------------------" << endl;
}

// -----------------------------------------------------------------------------

vector<string> reverseVectorNew(vector<string> v)
{
    vector<string> temp;
    for (int i = v.size() - 1; i >= 0; --i)
        temp.push_back(v[i]);
    
    return temp;
}

// -----------------------------------------------------------------------------

void reverseVectorRef(vector<string>& v)
{
    for (int i = 0; i < (v.size() / 2); ++i)
        swap(v[i], v[v.size() - (i + 1)]);
}

// -----------------------------------------------------------------------------

int reverseString()

{
    vector<string> v1{ "Write", "versions", "of", "the", "functions", "from", "exercise", "5", ", but", "with", "a", "vector<string>"};
    print(v1, "Vector 1: ");
    vector<string> v2 = reverseVectorNew(v1);
    print(v2, "Vector 2 - Reverse a vector by value: ");
    reverseVectorRef(v1);
    print(v1, "Vector 1 - Reverse a vector by reference: ");
    
    keep_window_open();
    return 0;
}
int main()

{
    vector<int> v1{1, 3, 5, 7, 9, 11};
    print(v1, "Vector 1: ");
    vector<int> v2 = reverseVectorNew(v1);
    print(v2, "Vector 2 - Reverse a vector by value: ");
    reverseVectorRef(v1);
    print(v1, "Vector 1 - Reverse a vector by reference: ");
    cout << "------------------------------------------\n";
    reverseString();
//    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
