// BitManipulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
using namespace std;

int IsBitSet(int oNum, int iPos)
{
    return (oNum & (1 << iPos)) != 0;
}

/*
Given an array of integers, every element appears thrice except for one which occurs once.
Find that element which does not appear thrice.
*/
void Find(int* pArray, int nSize)
{
    // Let say X is the number which is occuring exactly once
    // If X has set bit at ith position, then there are 3y + 1 number of 1's in the array at ith position
    // If X has unset bit at ith position, then there are 3y + 1 number of 0's in the array at ith position
    // So If the no. of 1's/0's are divisible by 3, then it is unset otherwise set

    int oResult = 0;

    for (int iCounter = 0; iCounter < 31; ++iCounter)
    {
        int OneCount = 0;
        for (int jCounter = 0; jCounter < nSize; ++jCounter)
        {
            if (IsBitSet(pArray[jCounter], iCounter)) {
                ++OneCount;
            }
        }

        if ((OneCount % 3) == 1)
            oResult = oResult | (1 << iCounter);
    }

    cout << oResult << endl;
}

/*
Given an array of integers, every element appears twice except for two elements which occurs once.
Find those two elements which does not appear twice.
*/
void Find(int* pArray, int nSize, int* p, int* q)
{
    int ResultantXOR = 0;
    for (int iCounter = 0; iCounter < nSize; ++iCounter)
        ResultantXOR ^= pArray[iCounter];

    int oFirstSetBitPos = 0;
    while (ResultantXOR != 0)
    {
        if (IsBitSet(ResultantXOR, oFirstSetBitPos))
            break; 

        ++oFirstSetBitPos;
    }

    int ResultantSetBitXOR = 0;
    int ResultantUnSetBitXOR = 0;

    for (int iCounter = 0; iCounter < nSize; ++iCounter)
    {
        if (IsBitSet(pArray[iCounter], oFirstSetBitPos))
            ResultantSetBitXOR ^= pArray[iCounter];
        else
            ResultantUnSetBitXOR ^= pArray[iCounter];
    }

    *p = ResultantSetBitXOR;
    *q = ResultantUnSetBitXOR;
}


/*
Given an array of n+2 elements. All elements of the array are in range 1 to n. 
All elements occur once except two numbers, which occur twice. 
Your task is to find the two repeating numbers.
*/
void FindRepeatingNumber(int* pArray, int nSize)
{
    int XOR_Value = 0;
    for (int iCounter = 0; iCounter < nSize; ++iCounter)
        XOR_Value ^= pArray[iCounter];

    for (int iCounter = 1; iCounter <= nSize - 2; ++iCounter)
        XOR_Value ^= iCounter;

    int oRightMostSetBit = XOR_Value & (~(XOR_Value - 1));
    int oSetXORValue = 0;
    int oUnsetXORValue = 0;


    for (int iCounter = 0; iCounter < nSize; ++iCounter)
    {
        if ((pArray[iCounter] & oRightMostSetBit) != 0)
            oSetXORValue ^= pArray[iCounter];
        else
            oUnsetXORValue ^= pArray[iCounter];
    }

    for (int iCounter = 1; iCounter <= nSize-2; ++iCounter)
    {
        if ((iCounter & oRightMostSetBit) != 0)
            oSetXORValue ^= iCounter;
        else
            oUnsetXORValue ^= iCounter;
    }

    if (oSetXORValue < oUnsetXORValue)
        cout << oSetXORValue << " " << oUnsetXORValue << endl;
    else
        cout << oSetXORValue << " " << oUnsetXORValue << endl;
}

/*
Given an array of integers, every element appears twice except for one element which occurs once.
Find that one element which does not appear twice.

Approach 1: Two nested loops: N^2,1
Approach 2: Take XOR of all elements: N, 1
Approach 3: If the Array is Sorted already, BinarySearch: LogN, 1
*/
int FindNonRepeatingNumber(int* pArray, int nSize)
{
    int Low = 0;
    int High = nSize - 1;

    while (Low <= High)
    {
        if (Low == High && Low >= 0 && Low <= nSize - 1)
            return pArray[Low];
         
        int Mid = Low + ((High - Low) >> 1);
        if (Mid & 1)
        { 
            // Mid is Odd
            if (pArray[Mid] == pArray[Mid - 1])
                Low = Mid + 1;
            else if (pArray[Mid] == pArray[Mid + 1])
                High = Mid - 1;
            else
                return pArray[Mid];

        }
        else
        { 
            // Mid is Even
            if (pArray[Mid] == pArray[Mid + 1])
                Low = Mid + 2;
            else if (pArray[Mid] == pArray[Mid - 1])
                High = Mid - 2;
            else
                return pArray[Mid];
        }
    }

}

int main()
{
    int pArray[] = { 1, 3 ,2 ,3, 4, 6, 5, 5, 6, 1, 2 };
    int nSize = 11;
    sort(pArray, pArray + nSize);
    cout << FindNonRepeatingNumber(pArray, nSize) << endl;
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
