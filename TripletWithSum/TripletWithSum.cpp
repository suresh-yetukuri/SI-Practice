// TripletWithSum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
using namespace std;

/*
 N^3, 1
*/
namespace UsingBruteForce
{
    bool IsSumTripletExist(int* pArray, int nSize, int kVal)
    {
        for (int iCounter = 0; iCounter < (nSize - 2); ++iCounter)
        {
            for (int jCounter = iCounter + 1; jCounter < (nSize-1); ++jCounter)
            { 
                for (int kCounter = jCounter + 1; kCounter < nSize; ++kCounter) 
                {
                    if ((pArray[iCounter] + pArray[jCounter] + pArray[kCounter]) == kVal)
                        return true;
                }
            }
        } 
        return false;
    }
}

/*
NLogN + N * NLogN, N
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

    bool IsSumTripletExist(int* pArray, int nSize, int kVal)
    {
        // NLogN, N
        sort(pArray, pArray + nSize);

        // N, 1
        for (int iCounter = 0; iCounter < nSize - 2; ++iCounter)
        {
            // N, 1
            for (int jCounter = iCounter + 1; jCounter < nSize - 1; ++jCounter)
            {
                // LogN, 1
                if (BinarySearch(pArray, jCounter + 1, nSize - 1, (kVal - pArray[jCounter])- pArray[iCounter]))
                    return true;
            } 
        }

        return false;
    }
}

/*
 NLogN + N*N, N
*/
namespace UsingPointerTechnique
{
    bool IsSumTripletExist(int* pArray, int nSize, int kVal)
    { 
        // NLogN, N
        sort(pArray, pArray + nSize);

        //N, 1
        for (int iCounter = 0; iCounter < nSize - 2; ++iCounter)
        {
            int pCounter = iCounter + 1;
            int qCounter = nSize - 1;

            // N, 1
            while (pCounter < qCounter)
            {
                int oCurrentSum = pArray[pCounter] + pArray[qCounter];
                if (oCurrentSum < (kVal-pArray[iCounter]))
                    ++pCounter;
                else if (oCurrentSum > (kVal - pArray[iCounter]))
                    --qCounter;
                else
                    return true;
            }
        }

        return false;
    }

}

int main()
{
    int pArray[] = { 12, 45, 52, 65, 21, 645, 234, - 100, 14, 575, - 80, 112 };
    int nSize = 12;
    int kVal = 54;
    cout << UsingBruteForce::IsSumTripletExist(pArray, nSize, kVal) << endl;
    cout << UsingBinarySearch::IsSumTripletExist(pArray, nSize, kVal) << endl;
    cout << UsingPointerTechnique::IsSumTripletExist(pArray, nSize, kVal) << endl;
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
