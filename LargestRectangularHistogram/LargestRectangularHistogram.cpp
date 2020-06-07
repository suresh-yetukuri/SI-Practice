
// LargestRectangularHistogram.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <stack>
#include<algorithm>
using namespace std;

/*
N(N+N), 1
*/
namespace BruteForce
{
    int getMaxArea(vector<int>& oInput)
    {
        int oMaxArea = -1;
        int nCount = static_cast<int>(oInput.size());
        for (int iCounter = 0; iCounter < nCount; ++iCounter)
        {
            int currValue = oInput[iCounter];
            for (int jCounter = iCounter - 1; jCounter >= 0; --jCounter)
            {
                if (oInput[jCounter] >= oInput[iCounter])
                    currValue += oInput[iCounter];
                else
                    break;
            }

            for (int jCounter = iCounter + 1; jCounter < nCount; ++jCounter)
            {
                if (oInput[jCounter] >= oInput[iCounter])
                    currValue += oInput[iCounter];
                else
                    break;
            }

            oMaxArea = max(oMaxArea, currValue);
        }

        return oMaxArea;
    }
}

/*
N+N+N,N+N
*/
namespace Optimized
{
    vector<int> GetPreviousSmaller(vector<int>& oInput)
    {
        int nCount = static_cast<int>(oInput.size());
        vector<int> oResult(nCount, -1);
        stack<int> pStack;
        for (int iCounter = 0; iCounter < nCount; ++iCounter)
        {
            int value = -1;
            while (!pStack.empty())
            {
                if (oInput[pStack.top()] < oInput[iCounter]) {
                    value = pStack.top();
                    break;
                }
                else {
                    pStack.pop();
                }
            }

            oResult[iCounter] = value;
            pStack.push(iCounter);
        }

        return move(oResult);
    }

    vector<int> GetNextSmaller(vector<int>& oInput)
    {
        int nCount = static_cast<int>(oInput.size());
        vector<int> oResult(nCount, nCount);
        stack<int> pStack;
        for (int iCounter = nCount - 1; iCounter >= 0; --iCounter)
        {
            int value = nCount;
            while (!pStack.empty())
            {
                if (oInput[pStack.top()] < oInput[iCounter]) {
                    value = pStack.top();
                    break;
                }
                pStack.pop();
            }

            oResult[iCounter] = value;
            pStack.push(iCounter);
        }

        return move(oResult);
    }

    int getMaxArea(vector<int>& oInput)
    {
        int oMaxArea = -1;
        int nCount = static_cast<int>(oInput.size());
        vector<int> oPS = GetPreviousSmaller(oInput);
        vector<int> oNS = GetNextSmaller(oInput);
        for (int iCounter = 0; iCounter < nCount; ++iCounter)
        {
            int currValue = oInput[iCounter];
            currValue += ((iCounter - oPS[iCounter] - 1) * oInput[iCounter]);
            currValue += ((oNS[iCounter] - iCounter - 1) * oInput[iCounter]);
            oMaxArea = max(oMaxArea, currValue);
        }

        return oMaxArea;
    }
}

/*
N + N, N
*/
namespace OptimizedII
{
    int getMaxArea(vector<int>& oInput)
    {
        int oMaxArea = -1;
        int nCount = static_cast<int>(oInput.size());
        stack<int> pStack;
        for (int iCounter = 0; iCounter < nCount; ++iCounter)
        {
            int currValue = 0;
            while (!pStack.empty() && oInput[pStack.top()] >= oInput[iCounter])
            {
                int value = pStack.top();
                pStack.pop();
                currValue = (oInput[value] * (pStack.empty() ? iCounter : (iCounter - pStack.top() - 1)));
                oMaxArea = max(oMaxArea, currValue);
            }
            pStack.push(iCounter);
        }

        while (!pStack.empty())
        {
            int value = pStack.top();
            pStack.pop();
            int currValue = oInput[value] * (pStack.empty() ? nCount : (nCount - pStack.top() - 1));
            oMaxArea = max(oMaxArea, currValue);
        }
         
        return oMaxArea;
    }
}


int main()
{
    vector<int> oInput{ 6, 2, 5, 4, 5, 1, 6 };
    cout << OptimizedII::getMaxArea(oInput);
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
