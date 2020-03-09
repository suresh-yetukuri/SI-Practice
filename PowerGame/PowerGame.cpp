// PowerGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
NLogN + NLogN + NLogN, N
*/
namespace UsingBinarySearch
{ 
    int GetWinningCount(int* pA, int* pB, int nSize)
    {
        int oWinningCount = 0;
        sort(pA, pA + nSize); 
        sort(pB, pB + nSize);
        int* pStartingPlayer = pA;
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            auto pItr = upper_bound(pStartingPlayer, pA + nSize, pB[iCounter]);
            if (pItr != (pA + nSize) ) {
                ++oWinningCount;
                pStartingPlayer = pItr + 1;
            }
        }

        return oWinningCount;
    }
}

namespace UsingTwoPointer
{
    int GetWinningCount(int* pA, int* pB, int nSize)
    {
        int oWinningCount = 0;
        sort(pA, pA + nSize);
        sort(pB, pB + nSize);

        int pCounter = 0;
        int qCounter = 0;

        while ((pCounter < nSize) && (qCounter < nSize))
        {
            if (pA[pCounter] > pB[qCounter])
            {
                ++oWinningCount;
                ++pCounter;
                ++qCounter;
            }
            else
            {
                ++pCounter;
            }
        }

        return oWinningCount;
    }
}

int main()
{ 
    int A[] = { 6 ,2};
    int B[] = { 5, 1 };
    int nSize = 2;
    int oWinningCount = UsingBinarySearch::GetWinningCount(A, B, nSize);
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
