// TripleTrouble.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

bool IsBitSet(unsigned int oNum, unsigned int Pos)
{
    return (oNum & (1 << Pos)) != 0;
}

unsigned int TripleTrouble(unsigned int* pArray, unsigned int nSize)
{
    unsigned int oResult = 0;
    for (unsigned int iCounter = 0u; iCounter <= 31; ++iCounter)
    {
        unsigned int oSetCount = 0;
        for (unsigned int jCounter = 0u; jCounter < nSize; ++jCounter)
        {
            if (IsBitSet(pArray[jCounter], iCounter))
                ++oSetCount;
        }

        if (0 != (oSetCount % 3))
            oResult |= (1 << iCounter);
    }

    return oResult;
}

int main()
{
    unsigned int arr[] = { 5u, 7u, 8u, 7u, 7u, 5u, 5u, 9u, 8u, 8u };
    cout << TripleTrouble(arr, 10) << endl;

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
