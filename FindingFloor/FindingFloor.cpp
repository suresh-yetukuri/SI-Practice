// FindingFloor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
using namespace std;

/*
Max(ar[i] <= x)
*/

/*
NLogN + N, N
*/
namespace UsingBinarySearch
{
    int FindingFloor(int* pArray, int nSize, int kVal)
    {
        sort(pArray, pArray + nSize);

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
            return pArray[Low];
        
        return INT_MIN;
    }
}

int main()
{
    int pArray[] = { -6, 10, -1, 20, 15, 5 };
    int nSize = 6;
    int kVal = -10;
    cout << UsingBinarySearch::FindingFloor(pArray, nSize, kVal);
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
