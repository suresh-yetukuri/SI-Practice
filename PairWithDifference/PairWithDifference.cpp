// PairWithDifference.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
using namespace std;

/*
 N^2, 1
*/
namespace BruteForce
{
    bool IsDiffPairExist(int* pArray, int nSize, int kVal)
    {
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            for (int jCounter = 0; jCounter < nSize; ++jCounter)
            {
                if ((iCounter != jCounter) && (pArray[iCounter] - pArray[jCounter]) == kVal)
                    return true;
            }
        }

        return false;
    }
}

/*
NLogN + N * LogN, N
*/
namespace UsingBinarySearch
{
    bool BinarySearch(int* pArray, int Low, int High, int kVal)
    {
        while (Low <= High)
        {
            int Mid = Low + ((High - Low) >> 1);

            if (pArray[Mid] < kVal)
                Low = Mid + 1;
            else if (pArray[Mid] > kVal)
                High = Mid - 1;
            else
                return true;
        }

        return false;
    }


    bool IsDiffPairExist(int* pArray, int nSize, int kVal)
    {
        sort(pArray, pArray + nSize);

        for (int iCounter = 0; iCounter < nSize - 1; ++iCounter)
        {
            if (BinarySearch(pArray, iCounter + 1, nSize - 1, kVal + pArray[iCounter]))
                return true;
        }

        return false;
    }
}

/*
 NLogN + N, N
*/
namespace PointerTechnique
{
    bool IsDiffPairExist(int* pArray, int nSize, int kVal)
    {
        sort(pArray, pArray + nSize);

        int pCounter = 0;
        int qCounter = pCounter + 1;

        while (pCounter < nSize && qCounter < nSize && pCounter != qCounter)
        {
            if (pCounter != qCounter)
            {
                int oCurrentDiff = pArray[pCounter] - pArray[qCounter];
                if (oCurrentDiff < kVal)
                    ++pCounter;
                else if (oCurrentDiff > kVal)
                    ++qCounter;
                else
                    return true;
            }
            else
            {
                ++pCounter;
            }

        }

        return false;
    }
}

/*
N, N
*/
namespace Hashing
{
    bool IsDiffPairExist(vector<int>& pArray, int nSize, int kVal)
    {
        unordered_set<int> oUSet;
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
        {
            int oTarget = (kVal + pArray[iCounter]);
            auto pItr = oUSet.find(oTarget);
            if (oUSet.end() != pItr)
                return true;
            oUSet.insert(pArray[iCounter]);
        }

        return false;
    }
}

int main()
{
    vector<int> arr{ 77, 28, 19, 21, 67, 15, 53, 25, 82, 52, 8, 94, 50, 30, 37, 39, 9, 43, 35, 48, 82, 53, 16, 20, 13, 95, 18, 67, 77, 12, 93, 0 };
    Hashing::IsDiffPairExist(arr, static_cast<int>(arr.size()), 53);
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
