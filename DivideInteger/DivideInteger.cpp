// DivideInteger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Divide(int a, int b)
{
    if ((a == INT_MIN) && (b == -1))
        return INT_MAX;


    int oDividend = abs(a);
    int oDivisor = abs(b);
    int oResult = 0;
    int sign = ((oDividend < 0) ^ (oDivisor < 0)) ? -1 : 1;
    while ((oDividend - oDivisor) >= 0)
    {
        int oMultiplier = 0;
        while ((oDividend - (oDivisor*(1 << oMultiplier))) >= 0)
        {
            ++oMultiplier;
        }

        oDividend = oDividend - (oDivisor * (1 << (oMultiplier-1)));
        oResult = oResult + (1 << (oMultiplier - 1));
    }

    return sign*oResult;
}
 
int main()
{
    cout << Divide(256, 7) << endl;
    cout << Divide(525, 25) << endl;
    cout << Divide(99, 16) << endl;
    cout << Divide(171, 6) << endl;
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
