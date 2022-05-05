//
// Created by renbin jiang on 2022/5/6.
//
// -----------------------------------------------------------------------------
//
//	C8 - Exercise 9
//
// -----------------------------------------------------------------------------

#include "std_lib_facilities.h"

// -----------------------------------------------------------------------------

double sumOfPriceWeightVectors(const vector<double>& prices, const vector<double>& weights, double& sum)
{
    if (prices.size() != weights.size())
        cout << "Whoopsie, not the same size." << endl;
    else
    {
        for (int i = 0; i < prices.size(); ++i)
        {
            sum += prices[i] * weights[i];
        }
    }
    
    return sum;
}

// -----------------------------------------------------------------------------

int main()

{
    vector<double> price{1.2, 3.2, 5.5, 4, 8.76, 90};
    vector<double> weight{1, 3, 5, 4, 7.7, 20.1};
    double sum(0);
    
    sumOfPriceWeightVectors(price, weight, sum);
    
    cout << "Sum: " << sum << endl;
    
    keep_window_open();
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
