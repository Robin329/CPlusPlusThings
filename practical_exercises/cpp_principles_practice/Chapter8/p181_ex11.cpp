//
// Created by renbin jiang on 2022/5/6.
//
// -----------------------------------------------------------------------------
//
//	C8 - Exercise 11
//
// -----------------------------------------------------------------------------

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

struct numbersInfo
{
    double maxNo, minNo;
    double mean, median;
};

// -----------------------------------------------------------------------------

void calculate(vector<double>& v, numbersInfo& nuI)
{
    nuI.maxNo = nuI.minNo = nuI.mean = nuI.median = v[0];
    
    if (v.size() == 1)
        return;
    
    //get min/max
    for (int i = 0; i < v.size(); ++i)
    {
        if (v[i] > nuI.maxNo)
            nuI.maxNo = v[i];
        if (v[i] < nuI.minNo)
            nuI.minNo = v[i];
        
        nuI.mean += v[i];
    }
    
    //get mean/median
    nuI.mean = nuI.mean / v.size();
    //sort for median
    sort(v.begin(), v.end());
    if (v.size() % 2 != 0)
        nuI.median = v[v.size() / 2];
    else
    {
        double v1 = v[(v.size() / 2.0f) - 1];
        double v2 = v[(v.size() / 2.0f)];
        nuI.median = (v1 + v2) / 2.0f;
    }
}

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

int main()

{
    vector<double> numbers{1, 200, 1001, 4, 50, 506};
    numbersInfo info;
    
    calculate(numbers, info);
    
    cout << "Max: " << info.maxNo << "\nMin: " << info.minNo << " \nMean: " << info.mean << " \nMedian: " << info.median << endl;
    
    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
