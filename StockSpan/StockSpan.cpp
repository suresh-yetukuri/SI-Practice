// StockSpan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
N^2, 1
*/
namespace BruteForce
{
    vector<int> GetStockSpan(vector<int>& oStockPrices)
    {
        int nCount = static_cast<int>(oStockPrices.size());
        vector<int> oSpan(nCount, 1);
        for (int iCounter = 0; iCounter < nCount; ++iCounter)
        {
            int jCounter = iCounter;
            while ((jCounter >= 0) && (oStockPrices[jCounter] <= oStockPrices[iCounter]))
                --jCounter;

            oSpan[iCounter] = iCounter - jCounter;
        }

        return move(oSpan);
    }
}

/*
N+N, N
*/
namespace UsingStack
{
    vector<int> GetStockSpan(vector<int>& oStockPrices)
    {
        int nCount = static_cast<int>(oStockPrices.size()); 
        vector<int> oSpan(nCount, 1);
        stack<int> pStack;
        for (int iCounter = 0; iCounter < nCount; ++iCounter)
        {
            int recentGreatestElement = -1;
            while (!pStack.empty())
            {
                if (oStockPrices[pStack.top()] <= oStockPrices[iCounter])
                    pStack.pop();
                else {
                    recentGreatestElement = pStack.top();
                    break;
                }
            }

            oSpan[iCounter] = iCounter - recentGreatestElement;
            pStack.push(iCounter);
        }

        return move(oSpan);
    }
}


int main()
{
    vector<int> oInput{ 0, 7, 3 ,6, 6, 9, 18, 0, 16, 0 };
    for (auto& x : oInput)
        cout << x << " ";

    cout << endl;
    vector<int> oResult(UsingStack::GetStockSpan(oInput));
    for (auto& x : oResult)
        cout << x << " ";

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
