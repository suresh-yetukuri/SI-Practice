// SumOfPairs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
using namespace std;


/*
 N^2, 1
*/
namespace UsingBruteForce
{
    bool IsSumPairExist(int* pArray, int nSize, int kVal)
    {
        for (int iCounter = 0; iCounter < (nSize - 1); ++iCounter)
        {
            for (int jCounter = iCounter + 1; jCounter < nSize; ++jCounter) 
            {
                if ((pArray[iCounter] + pArray[jCounter]) == kVal)
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


    bool IsSumPairExist(int* pArray, int nSize, int kVal)
    {
        sort(pArray, pArray + nSize);

        for (int iCounter = 0; iCounter < nSize - 1; ++iCounter)
        {
            if (BinarySearch(pArray, iCounter + 1, nSize - 1, kVal - pArray[iCounter]))
                return true;
        }

        return false;
    }
}

/*
 NLogN + N, N
*/
namespace UsingPointerTechnique
{
    bool IsSumPairExist(int* pArray, int nSize, int kVal)
    {
        sort(pArray, pArray + nSize);

        int pCounter = 0;
        int qCounter = nSize - 1;

        while (pCounter < qCounter)
        {
            int oCurrentSum = pArray[pCounter] + pArray[qCounter];
            if (oCurrentSum < kVal)
                ++pCounter;
            else if (oCurrentSum > kVal)
                --qCounter;
            else
                return true;

        }

        return false;
    }

}

int main()
{
    int pArray[] = { -30, 15, 20, 10, -10 };
    int nSize = 5;
    int kVal = -15;
    cout << UsingBruteForce::IsSumPairExist(pArray, nSize, kVal) << endl;
    cout << UsingBinarySearch::IsSumPairExist(pArray, nSize, kVal) << endl;
    cout << UsingPointerTechnique::IsSumPairExist(pArray, nSize, kVal) << endl;
   
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
