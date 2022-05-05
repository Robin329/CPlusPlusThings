//
// Created by renbin jiang on 2022/5/6.
//
// -----------------------------------------------------------------------------
//
//	C8 - Exercise 7
//
// -----------------------------------------------------------------------------

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

void printStringV(const vector<string>& v, const string& label)
{
    cout << label << endl;
    //for every int in vector, print that int
    for (string i : v)
        cout << i << " ";
}

// -----------------------------------------------------------------------------

void printNameAgePair(const vector<double>& vD, const vector<string>& vS, const string& label)
{
    cout << label << endl;
    for (int i = 0; i < vD.size(); ++i)
        cout << "Name: " << vS[i] << " Age: " << vD[i] << endl;
}

// -----------------------------------------------------------------------------

void sortNames(vector<double>& vD, vector<string>& vS)
{
    //create copies to refer to
    vector<double> tempAges = vD;
    vector<string> tempNames = vS;
    
    sort(vS.begin(), vS.end());
    //start with first sorted name, then check against unsorted to get correct index
    for (int i = 0; i < vD.size(); ++i)
    {
        for (int n = 0; n < vD.size(); ++n)
        {
            if (vS[i] == tempNames[n])
                vD[i] = tempAges[n];
        }
    }
}

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

void sortAge(vector<double>& vD, vector<string>& vS)
{
    //create copies to refer to
    vector<double> tempAges = vD;
    vector<string> tempNames = vS;
    
    sort(vD.begin(), vD.end());
    //start with first sorted name, then check against unsorted to get correct index
    for (int i = 0; i < vS.size(); ++i)
    {
        for (int n = 0; n < vS.size(); ++n)
        {
            if (vD[i] == tempAges[n])
                vS[i] = tempNames[n];
        }
    }
}

// -----------------------------------------------------------------------------

int main()

{
    vector<string> names{"zs", "lisi", "js", "robin", "lyy"};
    vector<double> ages{23, 24, 25, 26, 27};
    
    // cout << "Please enter 5 names >> ";
    // for (int i = 0; i < names.size(); ++i)
    // 	cin >> names[i];
    
    // for (int i = 0; i < names.size(); ++i)
    // {
    // 	cout << "How old is " << names[i] << "? >>";
    // 	cin >> ages[i];
    // }
    
    printNameAgePair(ages, names, "Name/Age Pairs - Unsorted");
    
    //sort names
    sortNames(ages, names);
    printNameAgePair(ages, names, "Name Pairs - Sorted");
    
    //sort ages
    sortAge(ages, names);
    printNameAgePair(ages, names, "Age Pairs - Sorted");
    
//    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
