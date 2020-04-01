// SlidingWindowMax.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <deque>
#include <algorithm>
using namespace std;

/*
Given an array of integers of size N and a window size K. 
For each continuous window of size K, find the highest element in the window. 
Output the sum of the highest element of all the windows.
*/

/*
(N-K+1)*K, 1
*/
namespace BruteForce
{
    long long int GetMax(vector<int>& oInput, int k)
    {
        int nSize = static_cast<int>(oInput.size());
        long long int oSum = 0;
        for (int iCounter = 0; iCounter < (nSize - k + 1); ++iCounter)
        {
            int oMax = INT_MIN;
            for (int jCounter = iCounter; jCounter < (iCounter + k); ++jCounter)
                oMax = max(oMax, oInput[jCounter]);

            oSum += static_cast<long long int>(oMax);
        }

        return oSum;
    }
}

/*
KLogK + (N-K)(LogK + LogK), K + K
Note: This is going to work only if 
we have distinct elements in input
*/
namespace Optimized
{
    long long int GetMax(vector<int>& oInput, int k)
    {
        int nSize = static_cast<int>(oInput.size());
        long long int oSum = 0;
        unordered_map<int, int> oHashMap;
        map<int, int, greater<int>> oMap;

        for (int iCounter = 0; iCounter < k; ++iCounter)
        {
            oHashMap[iCounter] = oInput[iCounter];
            oMap[oInput[iCounter]] = iCounter;
        }


        for (int iCounter = k; iCounter < nSize; ++iCounter)
        {  
            oSum += static_cast<long long int>(oMap.begin()->first);
            int x = oHashMap[iCounter - k];
            oHashMap.erase(iCounter - k);
            oMap.erase(x);
            oHashMap[iCounter] = oInput[iCounter];
            oMap[oInput[iCounter]] = iCounter;
        }
        oSum += oMap.begin()->first;
        return oSum;
    }
}


/*
Every element of input is going to be inserted
in deque only once and removed atmost once
N + N, K
*/
namespace OptimizedII
{
    long long int GetMax(vector<int>& oInput, int k)
    {
        int nSize = static_cast<int>(oInput.size());
        long long int oSum = 0;
        deque<int> oDeque;

        for (int iCounter = 0; iCounter < k; ++iCounter)
        {
            while ((!oDeque.empty()) && (oInput[oDeque.back()] <= oInput[iCounter]))
                oDeque.pop_back();

            oDeque.push_back(iCounter);
        }

        for (int iCounter = k; iCounter < nSize; ++iCounter)
        {
            oSum += static_cast<long long int>(oInput[oDeque.front()]);
            
            while ((!oDeque.empty()) && (oDeque.front() <= (iCounter - k)))
                oDeque.pop_front();

            while ((!oDeque.empty()) && (oInput[oDeque.back()] <= oInput[iCounter]))
                oDeque.pop_back();

            oDeque.push_back(iCounter);
        }

        oSum += static_cast<long long int>(oInput[oDeque.front()]);
        return oSum;
    }
}

int main()
{
    vector<int> oInput{ 4, 10, 54, 11, 8, 7, 9 };
    int k = 3;
    cout << OptimizedII::GetMax(oInput, k);
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
