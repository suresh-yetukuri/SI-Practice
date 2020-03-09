// Sorting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

namespace SortWithoutComparator
{
    void BubbleSort(int* pArray, int nSize)
    {
        for (int kPass = 0; kPass < nSize; ++kPass)
        {
            bool IsSwapped = false;
            for (int jCounter = 0; jCounter < nSize - kPass - 1; ++jCounter)
            {
                if (pArray[jCounter] > pArray[jCounter + 1])
                {
                    swap(pArray[jCounter], pArray[jCounter + 1]);
                    IsSwapped = true;
                }
            }

            if (!IsSwapped)break;
        }
    }

    void SelectionSort(int* pArray, int nSize)
    {
        for (int iCounter = 0; iCounter < nSize - 1; ++iCounter)
        {
            int iMinIdx = iCounter;

            for (int jCounter = iCounter + 1; jCounter < nSize; ++jCounter)
            {
                if (pArray[iMinIdx] > pArray[jCounter])
                    iMinIdx = jCounter;
            }

            swap(pArray[iMinIdx], pArray[iCounter]);
        }
    }

    void InsertionSort(int* pArray, int nSize)
    {
        for (int iCounter = 1; iCounter < nSize; ++iCounter)
        {
            int iHoleIdx = iCounter;
            int iHoleValue = pArray[iHoleIdx];

            while ((0 <= (iHoleIdx - 1)) && pArray[iHoleIdx - 1] > iHoleValue)
            {
                pArray[iHoleIdx] = pArray[iHoleIdx - 1];
                --iHoleIdx;
            }

            pArray[iHoleIdx] = iHoleValue;
        }
    }

    int Partition(int* pArray, int Start, int End)
    {
        int Pivot = pArray[End];
        int pIndex = Start;

        for (int iCounter = Start; iCounter < End; ++iCounter)
        {
            if (pArray[iCounter] <= Pivot)
            {
                swap(pArray[iCounter], pArray[pIndex]);
                ++pIndex;
            }
        }

        swap(pArray[pIndex], pArray[End]);
        return pIndex;
    }

    void QuickSort(int* pArray, int Start, int End)
    {
        if (Start < End)
        {
            int pIndex = Partition(pArray, Start, End);
            QuickSort(pArray, Start, pIndex - 1);
            QuickSort(pArray, pIndex + 1, End);
        }
    }
}

namespace SortWithComparator
{
    using Comparator = bool(*)(int, int);

    void BubbleSort(int* pArray, int nSize, Comparator oComparator)
    {
        for (int kPass = 0; kPass < nSize; ++kPass)
        {
            bool IsSwapped = false;
            for (int jCounter = 0; jCounter < nSize - kPass - 1; ++jCounter)
            {
                if (oComparator(pArray[jCounter], pArray[jCounter + 1]))
                {
                    swap(pArray[jCounter], pArray[jCounter + 1]);
                    IsSwapped = true;
                }
            }

            if (!IsSwapped)break;
        }
    }

    void SelectionSort(int* pArray, int nSize, Comparator oComparator)
    {
        for (int iCounter = 0; iCounter < nSize - 1; ++iCounter)
        {
            int iMinIdx = iCounter;

            for (int jCounter = iCounter + 1; jCounter < nSize; ++jCounter)
            {
                if (oComparator(pArray[iMinIdx], pArray[jCounter]))
                    iMinIdx = jCounter;
            }

            swap(pArray[iMinIdx], pArray[iCounter]);
        }
    }

    void InsertionSort(int* pArray, int nSize, Comparator oComparator)
    {
        for (int iCounter = 1; iCounter < nSize; ++iCounter)
        {
            int iHoleIdx = iCounter;
            int iHoleValue = pArray[iHoleIdx];

            while ((0 <= (iHoleIdx - 1)) && oComparator(pArray[iHoleIdx - 1], iHoleValue))
            {
                pArray[iHoleIdx] = pArray[iHoleIdx - 1];
                --iHoleIdx;
            }

            pArray[iHoleIdx] = iHoleValue;
        }
    }

    int Partition(int* pArray, int Start, int End, Comparator oComparator)
    {
        int Pivot = pArray[End];
        int pIndex = Start;

        for (int iCounter = Start; iCounter < End; ++iCounter)
        {
            if (oComparator(pArray[iCounter], Pivot))
            {
                swap(pArray[iCounter], pArray[pIndex]);
                ++pIndex;
            }
        }

        swap(pArray[pIndex], pArray[End]);
        return pIndex;
    }

    void QuickSort(int* pArray, int Start, int End, Comparator oComparator)
    {
        if (Start < End)
        {
            int pIndex = Partition(pArray, Start, End, oComparator);
            QuickSort(pArray, Start, pIndex - 1, oComparator);
            QuickSort(pArray, pIndex + 1, End, oComparator);
        }
    }
}


int main()
{
    auto oLamda = [](int a, int b)->bool {
        return a <= b;
    };
     
    int pArray[] = { 176, -272, -272, -45, 269, -327, -945, 176 };
    int nSize = 8;
    SortWithComparator::QuickSort(pArray, 0, 7, oLamda);

    // SortWithComparator::BubbleSort(pArray, nSize, oLamda);
    // SortWithComparator::SelectionSort(pArray, nSize, oLamda);
    // SortWithComparator::InsertionSort(pArray, nSize, oLamda);

    for (int iCounter = 0; iCounter < nSize; ++iCounter)
        cout << pArray[iCounter] << " ";
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
