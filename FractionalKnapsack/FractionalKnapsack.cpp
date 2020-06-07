// FractionalKnapsack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int value;
    int weight;
};

// function to return fractionalweights
double fractionalKnapsack(int W, Item arr[], int n)
{
    sort(arr, arr + n, [](Item& oFirst, Item& oSecond)->bool {
        double dFFraction = oFirst.value / (static_cast<double>(oFirst.weight));
        double dSFraction = oSecond.value / (static_cast<double>(oSecond.weight));
        return dFFraction > dSFraction;
        });

    double oMaxValue = 0.0;
    for (int iCounter = 0; iCounter < n; ++iCounter)
    {
        if (arr[iCounter].weight <= W)
        {
            oMaxValue += (arr[iCounter].value);
            W = W - arr[iCounter].weight;
        }
        else
        {
            oMaxValue += ((W / static_cast<double>(arr[iCounter].weight)) * arr[iCounter].value);
            break;
        }
    }

    return  oMaxValue;
}

int main()
{
    Item arr[] = { {60, 10}, {100, 20}, {120, 30} };
    int W = 50;
    int n = 3;
    cout << fractionalKnapsack(W, arr, n);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
