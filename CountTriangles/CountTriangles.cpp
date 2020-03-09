// CountTriangles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
using namespace std;



using TriangleValidator = bool(*)(int a, int b, int c);

namespace BruteForce
{
    int CountTriangles(int* pArray, int nSize, TriangleValidator oValidator)
    {
        int oValidCount = 0;
        for (int iCounter = 0; iCounter < nSize-2; ++iCounter) {
            for (int jCounter = iCounter + 1; jCounter < nSize-1; ++jCounter) {
                for (int kCounter = jCounter + 1; kCounter < nSize; ++kCounter)
                { 
                    if (oValidator(pArray[iCounter], pArray[jCounter], pArray[kCounter])) {
                        ++oValidCount;
                    } 
                }
            }
        }


        return oValidCount;
    }
}

namespace UsingBinarySearch
{
    int BinarySearch(int* pArray, int oTarget, int Low, int High)
    {
        while (Low < High)
        {
            int Mid = Low + ((High - Low + 1) >> 1);
            if ((oTarget - pArray[Mid]) > 0)
                Low = Mid;
            else
                High = Mid - 1;
        }

        if ((oTarget - pArray[Low]) > 0)
            return Low;

        return -1;
    }
    int CountTriangles(int* pArray, int nSize, TriangleValidator oValidator)
    {
        sort(pArray, pArray + nSize);
        int oValidCount = 0;
        for (int iCounter = 0; iCounter < nSize - 2; ++iCounter) {
            for (int jCounter = iCounter + 1; jCounter < nSize - 1; ++jCounter) 
            { 
                int Idx = BinarySearch(pArray, pArray[iCounter] + pArray[jCounter], jCounter + 1, nSize - 1);
                if (Idx != -1)
                    oValidCount = oValidCount + (Idx - jCounter);
            }
        }

        return oValidCount;
    }
}
int main()
{
    auto oValidator = [](int a, int b, int c)->bool {
        return ((a + b) > c) && ((b + c) > a) && ((c + a) > b);
    };

    /*int pArray[] = { 20, 67, 72, 83, 23, 59 };
    int nSize = 6;*/
    int pArray[] = { 4, 2, 10, 12, 8, 10 };
    int nSize = 6;
    
    cout << UsingBinarySearch::CountTriangles(pArray, nSize, oValidator);
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
