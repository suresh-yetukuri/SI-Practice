// SmallerElements.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
using namespace std;

/*
N^2, 1
*/
namespace UsingBruteForce
{
    int getSmallerCountRightSide(int* pArray, int nSize)
    {
        int oCount = 0;
        for (int iCounter = 0; iCounter < (nSize-1); ++iCounter)
        {
            for (int jCounter = iCounter + 1; jCounter < nSize; ++jCounter)
            {
                if ((iCounter != jCounter) && (pArray[iCounter] > pArray[jCounter]))
                    ++oCount;
            }
        }

        return oCount;
    }
}

/*
NLogN, N
*/
namespace UsingMergeSort
{
    int Merge(int* pArray, int* pLeft, int* pRight, int nLeft, int nRight)
    {
        int pCounter = 0;
        int qCounter = 0;
        int kCounter = 0;
        int Count = 0;

        while ((pCounter < nLeft) && (qCounter < nRight))
        {
            if (pLeft[pCounter] <= pRight[qCounter])
            {
                pArray[kCounter++] = pLeft[pCounter++];
            }
            else
            {
                Count += (nLeft - pCounter);
                pArray[kCounter++] = pRight[qCounter++];
            }
        }

        while (pCounter < nLeft)
        {
            pArray[kCounter++] = pLeft[pCounter++];
        }

        while (qCounter < nRight)
        {
            pArray[kCounter++] = pRight[qCounter++];
        }

        return Count;
    }

    int MergeCount(int* pArray, int nSize)
    {
        if (nSize < 2)
            return 0;

        int Count = 0;
        int Mid = nSize >> 1;

        int* pLeft = new int[Mid];
        int* pRight = new int[nSize - Mid];

        for (int iCounter = 0; iCounter < Mid; ++iCounter)
            pLeft[iCounter] = pArray[iCounter];

        for (int jCounter = Mid; jCounter < nSize; ++jCounter)
            pRight[jCounter - Mid] = pArray[jCounter];

         
        Count += MergeCount(pLeft, Mid);
        Count += MergeCount(pRight, nSize - Mid);
        Count += Merge(pArray, pLeft, pRight, Mid, nSize - Mid);

        delete[] pLeft; pLeft = nullptr;
        delete[] pRight; pRight = nullptr;

        return Count;
    }

    int getSmallerCountRightSide(int* pArray, int nSize)
    {
        return MergeCount(pArray, nSize);
    }
}

int main()
{
    int pArray[] = { 4, 10, 54, 11, 8 };
    int nSize = 5;
    cout << UsingMergeSort::getSmallerCountRightSide(pArray, nSize) << endl;
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
