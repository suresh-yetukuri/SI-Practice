// FindingFrequency.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

namespace UsingHash
{
    unordered_map<int, int> GetFrequecyArray(int* pArray, int nSize)
    {
        unordered_map<int, int> oUMap;
        for (int iCounter = 0; iCounter < nSize; ++iCounter)
            oUMap[pArray[iCounter]]++;

        return oUMap;
    }
}

namespace UsingBinarySearch
{
    int FindFloor(int* pArray, int nSize, int kVal)
    {
        int Low = 0;
        int High = nSize - 1;

        while (Low < High)
        {
            int Mid = Low + ((High - Low + 1) >> 1);
            if (pArray[Mid] <= kVal)
                Low = Mid;
            else
                High = Mid - 1;
        }

        if ((Low == High) && (pArray[Low] <= kVal))
            return Low;

        return -1; 
    }

    int FindCeil(int* pArray, int nSize, int kVal)
    {
        int Low = 0;
        int High = nSize - 1;

        while (Low < High)
        {
            int Mid = Low + ((High - Low) >> 1);
            if (pArray[Mid] >= kVal)
                High = Mid;
            else
                Low = Mid + 1;
        }

        if ((Low == High) && (pArray[Low] >= kVal))
            return Low;

        return -1; 
    }

    int GetFrequency(int* pArray, int nSize, int oQuery)
    {
        int LeftExtremeIdx = FindFloor(pArray, nSize, oQuery);
        int RightExtremeIdx = FindCeil(pArray, nSize, oQuery);

        if ((LeftExtremeIdx != -1) && (RightExtremeIdx != -1) && (LeftExtremeIdx <= RightExtremeIdx))
            return (RightExtremeIdx - LeftExtremeIdx + 1);

        return 0;
    }
}




int main()
{
    int nSize;
    cin >> nSize;

    int* pArray = new int[nSize];
    for (int jCounter = 0; jCounter < nSize; ++jCounter)
        cin >> pArray[jCounter];

    int nQueryCount;
    cin >> nQueryCount;

    int* pQueryArray = new int[nQueryCount];
    for (int jCounter = 0; jCounter < nQueryCount; ++jCounter)
        cin >> pQueryArray[jCounter];

    sort(pArray, pArray + nSize);

    for (int jCounter = 0; jCounter < nQueryCount; ++jCounter)
        cout << UsingBinarySearch::GetFrequency(pArray, nSize, pQueryArray[jCounter]) << endl;

    delete[] pArray;
    pArray = nullptr;

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
