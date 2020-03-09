// LargestConcatenatedNumber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
using namespace std;


int main()
{ 
    int pArray[] = { 69, 9, 57, 60 };
    int nSize = 4;
    auto oConcate = [](int x, int y)->int {
        int Power = 10;
        while (true)
        {
            if ((y % Power) == y) {
                break;
            }
            Power *= 10;
        }

        return (x * Power) + y;
    };
    auto oPredicate = [&](int a, int b)->bool {
        if (oConcate(a, b) > oConcate(b, a))
            return true;

        return false;
    };

    sort(pArray, pArray + nSize, oPredicate);

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
