// NearestSmallerElement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

/*
N^2, 1
*/
namespace BruteForce
{
    vector<int> GetPreviousGreater(vector<int>& oInput)
    {
        int nCount = static_cast<int>(oInput.size());
        vector<int> oResult(nCount, -1);
        for (int iCounter = 0; iCounter < nCount; ++iCounter)
        {
            int value = -1;
            int jCounter = iCounter - 1;
            while (jCounter >= 0)
            {
                if (oInput[jCounter] > oInput[iCounter]) {
                    value = oInput[jCounter];
                    break;
                }
                --jCounter;
            }
            oResult[iCounter] = value;
        }

        return move(oResult);
    }
}

/*
N+N, N
*/
namespace UsingStack
{
    vector<int> GetPreviousGreater(vector<int>& oInput)
    {
        int nCount = static_cast<int>(oInput.size());
        vector<int> oResult(nCount, 1);
        stack<int> pStack;
        for (int iCounter = 0; iCounter < nCount; ++iCounter)
        {
            int value = -1;
            while (!pStack.empty())
            {
                if (pStack.top() > oInput[iCounter]) {
                    value = pStack.top();
                    break;
                }
                else {
                    pStack.pop();
                }
            }

            oResult[iCounter] = value;
            pStack.push(oInput[iCounter]);
        }

        return move(oResult);
    }
}



int main()
{
    vector<int> oInput{ 20, 30, 10, 5, 15 };
    for (auto& x : oInput)
        cout << x << " ";

    cout << endl;
    vector<int> oResult(UsingStack::GetPreviousGreater(oInput));
    for (auto& x : oResult)
        cout << x << " ";

    return 0;
}